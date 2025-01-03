use std::io::{self, BufRead};

use ac_library::Dsu;
use itertools::Itertools;

#[derive(Clone, Copy, Debug)]
struct Crd(usize, usize);

impl Crd {
    fn distance(&self, other: Crd) -> usize {
        self.0.abs_diff(other.0) + self.1.abs_diff(other.1)
    }
}

fn connected_components(ps: &[Crd], max_distance: usize) -> Vec<Vec<Crd>> {
    let n = ps.len();
    let mut dsu = Dsu::new(n);

    for ((i, p), (j, q)) in ps.iter().enumerate().tuple_combinations() {
        if p.distance(*q) <= max_distance {
            dsu.merge(i, j);
        }
    }

    dsu.groups()
        .into_iter()
        .map(|ii| ii.into_iter().map(|i| ps[i]).collect())
        .collect()
}

fn constellation_size(ps: &[Crd], max_distance: usize) -> Option<usize> {
    let cs = connected_components(ps, max_distance);
    let qs = cs.first()?;
    if cs.len() == 1 {
        let total_d: usize = qs
            .iter()
            .combinations(2)
            .map(|pq| pq[0].distance(*pq[1]))
            .filter(|d| *d <= max_distance)
            .sum();
        Some(total_d + ps.len())
    } else {
        None
    }
}

fn main() {
    let grid: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let mut star_coordinates: Vec<Crd> = vec![];
    for (i, row) in grid.into_iter().enumerate() {
        for (j, cell) in row.into_iter().enumerate() {
            if cell == '*' {
                star_coordinates.push(Crd(i, j));
            }
        }
    }

    for hi in 1..100 {
        if let Some(s) = constellation_size(&star_coordinates, hi) {
            println!("{:?}", s);
            break;
        }
    }
}
