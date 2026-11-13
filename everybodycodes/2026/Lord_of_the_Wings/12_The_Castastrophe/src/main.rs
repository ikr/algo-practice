use ac_library::Dsu;
use std::io::{BufRead, stdin};

fn adjacent(ij: (usize, usize)) -> Vec<(usize, usize)> {
    let (i, j) = ij;
    let mut result = vec![(i + 1, j), (i, j + 1)];

    if i != 0 {
        result.push((i - 1, j));
    }

    if j != 0 {
        result.push((i, j - 1));
    }

    result
}

fn left_top(ps: &[(usize, usize)]) -> (usize, usize) {
    *ps.iter().min().unwrap()
}

fn right_bottom(ps: &[(usize, usize)]) -> (usize, usize) {
    *ps.iter().max().unwrap()
}

fn clusters(ps: &[(usize, usize)]) -> Vec<Vec<usize, usize>> {
    let n = ps.len();
    let g: Vec<Vec<usize>> = ps
        .iter()
        .map(|&ij| {
            adjacent(ij)
                .into_iter()
                .filter_map(|pq| ps.iter().position(|&uv| uv == pq))
                .collect()
        })
        .collect();
}

fn main() {
    let grid: Vec<Vec<u8>> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().bytes().collect())
        .collect();

    let magma: Vec<(usize, usize)> = grid
        .into_iter()
        .enumerate()
        .flat_map(move |(i, row)| {
            row.into_iter()
                .enumerate()
                .filter_map(move |(j, x)| (x == b'#').then_some((i, j)))
        })
        .collect();

    eprintln!("{magma:?}");
}
