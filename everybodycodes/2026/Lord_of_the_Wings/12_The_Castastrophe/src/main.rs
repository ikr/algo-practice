use ac_library::Dsu;
use std::{
    collections::HashSet,
    io::{BufRead, stdin},
};

fn main() {
    let grid: Vec<Vec<u8>> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().bytes().collect())
        .collect();

    let height = grid.len();
    let width = grid[0].len();

    let magma: HashSet<(usize, usize)> = grid
        .into_iter()
        .enumerate()
        .flat_map(|(i, row)| {
            row.into_iter()
                .enumerate()
                .filter_map(|(j, x)| (x == b'#').then_some((i, j)))
        })
        .collect();
}
