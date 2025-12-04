use itertools::Itertools;
use std::io::{BufRead, stdin};

fn neighs(grid: &[Vec<u8>], ro: usize, co: usize) -> Vec<(usize, usize)> {
    let (i, j) = (ro as i32, co as i32);
    let (h, w) = (grid.len() as i32, grid[0].len() as i32);

    (-1..=1)
        .cartesian_product(-1..=1)
        .filter_map(|(di, dj)| {
            if di != 0 || dj != 0 {
                let (ii, jj) = (i + di, j + dj);
                (0 <= ii && ii < h && 0 <= jj && jj < w).then_some((ii as usize, jj as usize))
            } else {
                None
            }
        })
        .collect()
}

fn roll_neighs_count(grid: &[Vec<u8>], ro: usize, co: usize) -> usize {
    neighs(grid, ro, co)
        .into_iter()
        .filter(|&(i, j)| grid[i][j] == b'@')
        .count()
}

fn main() {
    let mut grid: Vec<Vec<u8>> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().bytes().collect())
        .collect();

    let (h, w) = (grid.len(), grid[0].len());
    let mut result = 0;

    loop {
        let q: Vec<(usize, usize)> = (0..h)
            .cartesian_product(0..w)
            .filter(|&(i, j)| grid[i][j] == b'@' && roll_neighs_count(&grid, i, j) < 4)
            .collect();

        if q.is_empty() {
            break;
        }

        result += q.len();
        for (i, j) in q {
            grid[i][j] = b'.';
        }
    }
    eprintln!("{result}");
}
