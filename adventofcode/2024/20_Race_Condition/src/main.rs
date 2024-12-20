use std::{
    collections::{HashMap, VecDeque},
    io::{self, BufRead},
};

use itertools::Itertools;

const INF: usize = 10_000_000;

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

fn optimal_path(grid: &[Vec<char>], start: Crd, end: Crd) -> Vec<Crd> {
    if start == end {
        return vec![start];
    }

    let mut distance: HashMap<Crd, u32> = HashMap::from([(start, 0)]);
    let mut pre: HashMap<Crd, Crd> = HashMap::new();
    let mut queue: VecDeque<Crd> = VecDeque::from([start]);
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

    while let Some(p) = queue.pop_front() {
        for q in adjacent(p) {
            if !distance.contains_key(&q) {
                distance.insert(q, distance[&p] + 1);
                pre.insert(q, p);
                queue.push_back(q);
            }
        }
    }

    let mut path = vec![];
    let mut p = end;

    loop {
        path.push(p);
        if !pre.contains_key(&p) {
            break;
        }
        p = pre[&p];
    }

    path.reverse();
    path
}

fn optimal_distance_in_the_walls_under_20(grid: &[Vec<char>], start: Crd, end: Crd) -> usize {
    for p in [start, end] {
        assert_ne!(grid[p.0 as usize][p.1 as usize], '#');
    }

    if start == end {
        return 0;
    }

    let in_bounds = |c: Crd| -> bool {
        0 <= c.0 && c.0 < grid.len() as i16 && 0 <= c.1 && c.1 < grid[0].len() as i16
    };

    let cell_at = |c: Crd| -> char { grid[c.0 as usize][c.1 as usize] };

    let adjacent = |p: Crd| -> Vec<Crd> {
        Dir::all()
            .iter()
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

    let mut distance: HashMap<Crd, usize> = HashMap::from([(start, 0)]);
    let mut queue: VecDeque<Crd> = VecDeque::from([start]);

    while let Some(p) = queue.pop_front() {
        for q in adjacent(p) {
            if !distance.contains_key(&q) && distance[&p] < 20 {
                if q == end {
                    return distance[&p] + 1;
                }

                if cell_at(q) == '#' {
                    distance.insert(q, distance[&p] + 1);
                    queue.push_back(q);
                }
            }
        }
    }

    INF
}

// fn eprintln_grid(grid: &[Vec<char>]) {
//     for row in grid {
//         eprintln!("{}", row.iter().collect::<String>());
//     }
//     eprintln!();
// }

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
    let initial_path = optimal_path(&grid, start, end);
    let initial_distance = initial_path.len() - 1;
    eprintln!("initial_distance:{}", initial_distance);

    let savings: Vec<usize> = initial_path
        .iter()
        .cloned()
        .enumerate()
        .combinations(2)
        .map(|iajb| {
            let [(i, a), (j, b)] = iajb[..] else { panic!() };
            assert!(i < j);
            let warp = optimal_distance_in_the_walls_under_20(&grid, a, b);
            (j - i).saturating_sub(warp)
        })
        .collect();

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
