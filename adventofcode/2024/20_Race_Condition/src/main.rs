use std::{
    collections::{HashMap, HashSet, VecDeque},
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
    if start == end {
        return 0;
    }

    let mut seen: HashSet<Crd> = HashSet::from([start]);
    let mut queue: VecDeque<(Crd, u32)> = VecDeque::from([(start, 0)]);
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

fn gather_non_walls(grid: &[Vec<char>]) -> Vec<Crd> {
    let mut result = vec![];
    for (i, row) in grid.iter().enumerate() {
        for (j, &cell) in row.iter().enumerate() {
            if cell != '#' {
                result.push(Crd(i as i16, j as i16));
            }
        }
    }
    result
}

fn wormhole_exits(grid: &[Vec<char>], source: Crd, first_wall: Crd) -> Vec<(Crd, u32)> {
    let mut result = vec![];
    let mut seen: HashSet<Crd> = HashSet::from([source, first_wall]);
    let mut queue: VecDeque<(Crd, u32)> = VecDeque::from([(first_wall, 1)]);

    let in_bounds = |c: Crd| -> bool {
        c.0 >= 0 && c.0 < grid.len() as i16 && c.1 >= 0 && c.1 < grid[0].len() as i16
    };

    let cell_at = |c: Crd| -> char { grid[c.0 as usize][c.1 as usize] };

    assert_ne!(cell_at(source), '#');
    assert_eq!(cell_at(first_wall), '#');

    let adjacent = |p: Crd| -> Vec<Crd> {
        Dir::all()
            .into_iter()
            .filter_map(|d| {
                let q = p + d.delta();
                if in_bounds(q) {
                    Some(q)
                } else {
                    None
                }
            })
            .collect()
    };

    while let Some((p, d)) = queue.pop_front() {
        assert!(d < 20);

        for q in adjacent(p) {
            if cell_at(q) == '#' {
                if d < 19 && !seen.contains(&q) {
                    queue.push_back((q, d + 1));
                }
            } else if !seen.contains(&q) {
                result.push((q, d + 1));
            }

            seen.insert(q);
        }
    }
    result
}

fn wormhole_entrances(grid: &[Vec<char>], source: Crd) -> Vec<Crd> {
    assert_ne!(grid[source.0 as usize][source.1 as usize], '#');
    Dir::all()
        .into_iter()
        .filter_map(|d| {
            let q = source + d.delta();
            if grid[q.0 as usize][q.1 as usize] == '#' {
                Some(q)
            } else {
                None
            }
        })
        .collect()
}

fn eprintln_grid(grid: &[Vec<char>]) {
    for row in grid {
        eprintln!("{}", row.iter().collect::<String>());
    }
    eprintln!();
}

fn main() {
    let grid: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let crd_of = |c: char| -> Crd {
        for (i, row) in grid.iter().enumerate() {
            if let Some(j) = row.iter().position(|&x| x == c) {
                return Crd(i as i16, j as i16);
            }
        }
        panic!();
    };

    let start = crd_of('S');
    let end = crd_of('E');
    assert_eq!(optimal_distance(&grid, start, start), 0);
    let initial_distance = optimal_distance(&grid, start, end);
    eprintln!("initial_distance:{}", initial_distance);

    let mut warps_by_source_and_exit: HashMap<(Crd, Crd), u32> = HashMap::new();

    for source in gather_non_walls(&grid) {
        for entrance in wormhole_entrances(&grid, source) {
            for (exit, warp) in wormhole_exits(&grid, source, entrance) {
                warps_by_source_and_exit
                    .entry((source, exit))
                    .and_modify(|w| {
                        if &warp < w {
                            *w = warp;
                        }
                    })
                    .or_insert(warp);
            }
        }
    }

    let mut savings: Vec<u32> = vec![];
    for ((source, exit), warp) in warps_by_source_and_exit {
        let distance =
            optimal_distance(&grid, start, source) + warp + optimal_distance(&grid, exit, end);
        let saved = initial_distance.saturating_sub(distance);
        if saved != 0 {
            savings.push(saved);
        }
    }

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
