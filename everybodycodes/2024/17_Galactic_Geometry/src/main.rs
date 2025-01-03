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

fn min_spanning_tree_total_distance(ps: &[Crd]) -> usize {
    let n = ps.len();
    let mut edges: Vec<(usize, usize)> = (0..n).combinations(2).map(|ij| (ij[0], ij[1])).collect();
    edges.sort_by_key(|(i, j)| ps[*i].distance(ps[*j]));

    let mut dsu = Dsu::new(n);
    let mut result = 0;
    for (i, j) in edges {
        if dsu.leader(i) != dsu.leader(j) {
            result += ps[i].distance(ps[j]);
            dsu.merge(i, j);
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

    let mut star_coordinates: Vec<Crd> = vec![];
    for (i, row) in grid.into_iter().enumerate() {
        for (j, cell) in row.into_iter().enumerate() {
            if cell == '*' {
                star_coordinates.push(Crd(i, j));
            }
        }
    }

    let mut ss: Vec<usize> = connected_components(&star_coordinates, 5)
        .into_iter()
        .map(|ps| min_spanning_tree_total_distance(&ps) + ps.len())
        .collect();
    ss.sort();
    let n = ss.len();
    let result: usize = ss[n - 3..n].iter().product();
    println!("{}", result);
}
