use std::{
    collections::{HashMap, VecDeque},
    io::{self, BufRead},
};

use itertools::Itertools;

const INF: usize = 10_000_000;

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(usize, usize);

impl Crd {
    fn north(&self) -> Option<Crd> {
        if self.0 != 0 {
            Some(Crd(self.0 - 1, self.1))
        } else {
            None
        }
    }

    fn east(&self, w: usize) -> Option<Crd> {
        if self.1 < w - 1 {
            Some(Crd(self.0, self.1 + 1))
        } else {
            None
        }
    }

    fn south(&self, h: usize) -> Option<Crd> {
        if self.0 < h - 1 {
            Some(Crd(self.0 + 1, self.1))
        } else {
            None
        }
    }

    fn west(&self) -> Option<Crd> {
        if self.1 != 0 {
            Some(Crd(self.0, self.1 - 1))
        } else {
            None
        }
    }

    fn adjacent(&self, h: usize, w: usize) -> Vec<Crd> {
        [self.north(), self.east(w), self.south(h), self.west()]
            .iter()
            .filter_map(|x| *x)
            .collect()
    }
}

fn bfs(grid: &[Vec<char>], start: Crd) -> (Vec<Vec<usize>>, Vec<Vec<Option<Crd>>>) {
    let h = grid.len();
    let w = grid[0].len();

    let mut distance: Vec<Vec<usize>> = vec![vec![INF; w]; h];
    distance[start.0][start.1] = 0;

    let mut pre: Vec<Vec<Option<Crd>>> = vec![vec![None; w]; h];
    let mut queue: VecDeque<Crd> = VecDeque::from([start]);

    let adjacent = |p: Crd| -> Vec<Crd> {
        p.adjacent(h, w)
            .into_iter()
            .filter(|q| grid[q.0][q.1] != '#')
            .collect()
    };

    while let Some(p) = queue.pop_front() {
        for q in adjacent(p) {
            if distance[q.0][q.1] == INF {
                distance[q.0][q.1] = distance[p.0][p.1] + 1;
                pre[q.0][q.1] = Some(p);
                queue.push_back(q);
            }
        }
    }

    (distance, pre)
}

fn recover_path(pre: &[Vec<Option<Crd>>], end: Crd) -> Vec<Crd> {
    let mut path = vec![];
    let mut p = end;

    loop {
        path.push(p);
        if let Some(pp) = pre[p.0][p.1] {
            p = pp;
        } else {
            break;
        }
    }

    path.reverse();
    path
}

fn optimal_distances_through_the_walls_up_to_k(
    k: usize,
    grid: &[Vec<char>],
    start: Crd,
) -> HashMap<Crd, usize> {
    assert_ne!(grid[start.0][start.1], '#');

    let h = grid.len();
    let w = grid[0].len();
    let mut distances: HashMap<Crd, usize> = HashMap::from([(start, 0)]);
    let mut queue: VecDeque<Crd> = VecDeque::from([start]);

    while let Some(p) = queue.pop_front() {
        for q in p.adjacent(h, w) {
            if !distances.contains_key(&q) && distances[&p] < k {
                distances.insert(q, distances[&p] + 1);
                queue.push_back(q);
            }
        }
    }

    distances
}

fn non_wall_coordinates(grid: &[Vec<char>]) -> Vec<Crd> {
    let mut result: Vec<Crd> = vec![];
    for (i, row) in grid.iter().enumerate() {
        for (j, &cell) in row.iter().enumerate() {
            if cell != '#' {
                result.push(Crd(i, j));
            }
        }
    }
    result
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
                return Crd(i, j);
            }
        }
        panic!();
    };

    let start = crd_of('S');
    let end = crd_of('E');

    let (start_d, start_pre) = bfs(&grid, start);
    let (end_d, _) = bfs(&grid, end);

    let initial_path = recover_path(&start_pre, end);
    let initial_distance = start_d[end.0][end.1];
    assert_eq!(initial_distance, initial_path.len() - 1);
    eprintln!("initial_distance:{}", initial_distance);

    let savings: Vec<usize> = non_wall_coordinates(&grid)
        .into_iter()
        .flat_map(|p| {
            let dpqs = optimal_distances_through_the_walls_up_to_k(20, &grid, p);
            let mut result: Vec<usize> = vec![];
            for (q, dpq) in dpqs {
                if grid[q.0][q.1] != '#' {
                    let d = start_d[p.0][p.1] + dpq + end_d[q.0][q.1];
                    if d < initial_distance {
                        result.push(initial_distance - d);
                    }
                }
            }
            result
        })
        .collect();

    let fq: Vec<_> = savings
        .iter()
        .filter(|&&d| d >= 50)
        .counts()
        .into_iter()
        .sorted()
        .collect();
    eprintln!("{:?}", fq);

    let result = savings.into_iter().filter(|&d| d >= 100).count();
    println!("{}", result);
}
