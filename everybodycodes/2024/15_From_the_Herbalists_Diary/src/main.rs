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
                if v == destination {
                    return distances[&u] + 1;
                }
                distances.insert(v, distances[&u] + 1);
                q.push_back(v);
            }
        }
    }

    panic!("Couldn't reach the destination")
}

#[memoize(Ignore: grid, Ignore: source, Ignore: herb_kind_crds)]
fn min_route_length(
    grid: &[Vec<u8>],
    source: Crd,
    herb_kind_crds: &HashMap<u8, Vec<Crd>>,
    visited_kind_bits: u16,
    last_visited_kind_index: u8,
    last_visited_crd_index: u8,
) -> u16 {
    let ks: Vec<u8> = herb_kind_crds.keys().copied().sorted().collect();
    assert!(last_visited_kind_index < ks.len() as u8);
    assert!(
        last_visited_crd_index < herb_kind_crds[&ks[last_visited_kind_index as usize]].len() as u8
    );

    if visited_kind_bits.count_ones() == 1 {
        min_distance(
            grid,
            source,
            herb_kind_crds[&ks[last_visited_kind_index as usize]][last_visited_crd_index as usize],
        )
    } else {
        let mut sub = u16::MAX;
        let n = ks.len() as u8;
        for i in 0..n {
            if i != last_visited_kind_index && (1u16 << i) & visited_kind_bits != 0 {
                for j in 0..herb_kind_crds[&ks[i as usize]].len() as u8 {
                    sub = sub.min(
                        min_distance(
                            grid,
                            herb_kind_crds[&ks[last_visited_kind_index as usize]]
                                [last_visited_crd_index as usize],
                            herb_kind_crds[&ks[i as usize]][j as usize],
                        ) + min_route_length(
                            grid,
                            source,
                            herb_kind_crds,
                            visited_kind_bits ^ (1u16 << last_visited_kind_index),
                            i,
                            j,
                        ),
                    );
                }
            }
        }
        sub
    }
}

fn main() {
    let grid: Vec<Vec<u8>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().bytes().collect())
        .collect();

    let source_column = grid[0].iter().position(|&x| x == b'.').unwrap();
    let source = Crd(0, source_column as i16);

    let herb_kind_crds = {
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

    let herb_kind_counts = herb_kind_crds
        .values()
        .map(|ps| ps.len())
        .sorted()
        .collect::<Vec<_>>();

    eprintln!(
        "There are {} herb kinds; counts per kind: {:?}; Π:{}",
        herb_kind_crds.len(),
        herb_kind_counts,
        herb_kind_counts.iter().product::<usize>()
    );

    let ks: Vec<u8> = herb_kind_crds.keys().copied().sorted().collect();
    let n = ks.len() as u8;
    let visited_kind_bits = (1u16 << n) - 1;
    let mut result: u16 = u16::MAX;

    for i in 0..n {
        for j in 0..herb_kind_crds[&ks[i as usize]].len() as u8 {
            let crd = herb_kind_crds[&ks[i as usize]][j as usize];
            result = result.min(
                min_route_length(&grid, source, &herb_kind_crds, visited_kind_bits, i, j)
                    + min_distance(&grid, source, crd),
            )
        }
    }

    println!("{}", result);
}
