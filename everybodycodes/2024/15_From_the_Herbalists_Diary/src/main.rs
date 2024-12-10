use std::{
    collections::{HashMap, VecDeque},
    io::{self, BufRead},
};

use itertools::Itertools;
use memoize::memoize;

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i16, i16);

#[memoize(Ignore: grid)]
fn min_distance(grid: &[Vec<u8>], source: Crd, destination: Crd) -> u16 {
    let in_bounds = |crd: Crd| -> bool {
        0 <= crd.0 && crd.0 < grid.len() as i16 && 0 <= crd.1 && crd.1 < grid[0].len() as i16
    };

    let cell_at = |crd: Crd| -> u8 { grid[crd.0 as usize][crd.1 as usize] };

    let adjacent = |crd: Crd| -> Vec<Crd> {
        let Crd(ro, co) = crd;
        [
            Crd(ro - 1, co),
            Crd(ro, co + 1),
            Crd(ro + 1, co),
            Crd(ro, co - 1),
        ]
        .into_iter()
        .filter(|crd| in_bounds(*crd) && cell_at(*crd) != b'#' && cell_at(*crd) != b'~')
        .collect()
    };

    let mut distances: HashMap<Crd, u16> = HashMap::from([(source, 0)]);
    let mut q: VecDeque<Crd> = VecDeque::from([source]);

    while let Some(u) = q.pop_front() {
        for v in adjacent(u) {
            if !distances.contains_key(&v) {
                distances.insert(v, distances[&u] + 1);
                q.push_back(v);
            }
        }
    }

    distances[&destination]
}

fn main() {
    let grid: Vec<Vec<u8>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().bytes().collect())
        .collect();

    let source_column = grid[0].iter().position(|&x| x == b'.').unwrap();
    let source = Crd(0, source_column as i16);

    let herbs_by_node = {
        let mut result: HashMap<u8, Vec<Crd>> = HashMap::new();
        for (i, row) in grid.iter().enumerate() {
            for (j, &cell) in row.iter().enumerate() {
                if cell.is_ascii_uppercase() {
                    result
                        .entry(cell)
                        .or_default()
                        .push(Crd(i as i16, j as i16));
                }
            }
        }
        result
    };

    let herb_kind_counts = herbs_by_node
        .values()
        .map(|ps| ps.len())
        .sorted()
        .collect::<Vec<_>>();

    eprintln!(
        "There are {} herb kinds; counts per kind: {:?}; Π:{}",
        herbs_by_node.len(),
        herb_kind_counts,
        herb_kind_counts.iter().product::<usize>()
    );

    let ks = herbs_by_node.keys().collect::<Vec<_>>();
    let m = ks.len();
    let mut result: u16 = 20_000;

    for herbs_indices in ks.into_iter().permutations(m) {
        for mut plan in herbs_indices
            .into_iter()
            .map(|k| herbs_by_node[&k].clone())
            .multi_cartesian_product()
        {
            plan.insert(0, source);
            plan.push(source);

            let candidate = plan
                .windows(2)
                .map(|pq| {
                    let [p, q] = pq else { panic!() };
                    min_distance(&grid, *p, *q)
                })
                .sum();
            if candidate < result {
                result = candidate;
                eprintln!("{}", result);
            }
        }
    }

    println!("{}", result);
}
