use itertools::Itertools;
use std::io::{BufRead, stdin};

fn neighs(grid: &[Vec<u8>], ro: usize, co: usize) -> Vec<(usize, usize)> {
    let i: i64 = ro as i64;
    let j: i64 = co as i64;
    let h = grid.len() as i64;
    let w = grid[0].len() as i64;
    let mut result = vec![];

    for di in -1..=1 {
        for dj in -1..=1 {
            if di == 0 && dj == 0 {
                continue;
            }

            let ii = i + di;
            let jj = j + dj;

            if 0 <= ii && ii < h && 0 <= jj && jj < w {
                result.push((ii as usize, jj as usize));
            }
        }
    }

    result
}

fn roll_neighs_count(grid: &[Vec<u8>], ro: usize, co: usize) -> usize {
    neighs(grid, ro, co)
        .into_iter()
        .filter(|&(i, j)| grid[i][j] == b'@')
        .count()
}

fn main() {
    let grid: Vec<Vec<u8>> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().bytes().collect())
        .collect();

    let h = grid.len();
    let w = grid[0].len();

    let result = (0..h)
        .cartesian_product(0..w)
        .filter(|&(i, j)| grid[i][j] == b'@' && roll_neighs_count(&grid, i, j) < 4)
        .count();

    eprintln!("{result}");
}
