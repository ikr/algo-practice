use std::{
    collections::{HashSet, VecDeque},
    io::{self, BufRead},
};

use itertools::Itertools;

const INF: u32 = 1_000_000;

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i16, i16);

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

#[derive(Clone, Copy, Debug)]
enum Dir {
    N,
    E,
    S,
    W,
}

impl Dir {
    fn all() -> Vec<Dir> {
        vec![Dir::N, Dir::E, Dir::S, Dir::W]
    }

    fn opposite(&self) -> Dir {
        match self {
            Dir::N => Dir::S,
            Dir::E => Dir::W,
            Dir::S => Dir::N,
            Dir::W => Dir::E,
        }
    }

    fn delta(&self) -> Crd {
        match self {
            Dir::N => Crd(-1, 0),
            Dir::E => Crd(0, 1),
            Dir::S => Crd(1, 0),
            Dir::W => Crd(0, -1),
        }
    }
}

fn optimal_distance(grid: &[Vec<char>], start: Crd, end: Crd) -> u32 {
    let mut seen: HashSet<Crd> = HashSet::new();
    seen.insert(start);

    let mut queue: VecDeque<(Crd, u32)> = VecDeque::new();
    queue.push_back((start, 0));

    let cell_at = |c: Crd| -> char { grid[c.0 as usize][c.1 as usize] };

    let adjacent = |p: Crd| -> Vec<Crd> {
        Dir::all()
            .iter()
            .filter_map(|d| {
                let q = p + d.delta();
                if cell_at(q) != '#' {
                    Some(q)
                } else {
                    None
                }
            })
            .collect()
    };

    while let Some((p, d)) = queue.pop_front() {
        for q in adjacent(p) {
            if q == end {
                return d + 1;
            }

            if !seen.contains(&q) {
                seen.insert(q);
                queue.push_back((q, d + 1));
            }
        }
    }

    INF
}

fn possible_cheats(grid: &[Vec<char>]) -> Vec<(Crd, Dir)> {
    let in_bounds = |c: Crd| -> bool {
        c.0 >= 0 && c.0 < grid.len() as i16 && c.1 >= 0 && c.1 < grid[0].len() as i16
    };

    let mut result = vec![];
    for (i, row) in grid.iter().enumerate() {
        for (j, &cell) in row.iter().enumerate() {
            if cell == '.' {
                let u = Crd(i as i16, j as i16);
                for d in Dir::all() {
                    let p = u + d.delta();
                    let q = p + d.delta();
                    if grid[p.0 as usize][p.1 as usize] == '#'
                        && in_bounds(q)
                        && grid[q.0 as usize][q.1 as usize] != '#'
                    {
                        result.push((p, d));
                    }
                }
            }
        }
    }
    result
}

fn main() {
    let initial_grid: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let crd_of = |c: char| -> Crd {
        for (i, row) in initial_grid.iter().enumerate() {
            if let Some(j) = row.iter().position(|&x| x == c) {
                return Crd(i as i16, j as i16);
            }
        }
        panic!();
    };

    let start = crd_of('S');
    let end = crd_of('E');
    let initial_distance = optimal_distance(&initial_grid, start, end);

    let mut grid = initial_grid.clone();

    let savings = possible_cheats(&initial_grid)
        .into_iter()
        .map(|(p, d)| {
            let q = p + d.delta();
            let original_p = grid[p.0 as usize][p.1 as usize];
            let original_q = grid[q.0 as usize][q.1 as usize];

            let pre_p = p + d.opposite().delta();
            let one = optimal_distance(&grid, start, pre_p);

            grid[p.0 as usize][p.1 as usize] = '1';
            grid[q.0 as usize][q.1 as usize] = '2';

            let distance = one + 1 + optimal_distance(&grid, p, end);

            grid[p.0 as usize][p.1 as usize] = original_p;
            grid[q.0 as usize][q.1 as usize] = original_q;
            initial_distance.saturating_sub(distance)
        })
        .collect::<Vec<_>>();

    let mut fq = savings
        .iter()
        .filter(|&&d| d >= 50)
        .copied()
        .filter(|d| *d > 0)
        .counts()
        .into_iter()
        .collect::<Vec<_>>();
    fq.sort();
    eprintln!("{:?}", fq);

    let result = savings.iter().filter(|&&d| d >= 100).count();
    println!("{}", result);
}
