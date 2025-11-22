use itertools::Itertools;
use std::{
    collections::VecDeque,
    io::{BufRead, stdin},
};

fn true_count(xss: &[Vec<bool>]) -> usize {
    xss.iter()
        .map(|row| row.iter().filter(|x| **x).count())
        .sum()
}

fn explosion_yield(
    grid: &[Vec<u8>],
    exploded: &mut [Vec<bool>],
    first_barrel: (usize, usize),
) -> usize {
    let h = grid.len();
    let w = grid[0].len();
    let baseline = true_count(exploded);
    exploded[first_barrel.0][first_barrel.1] = true;
    let mut q: VecDeque<(usize, usize)> = VecDeque::from([first_barrel]);

    while let Some((i, j)) = q.pop_front() {
        if i != 0 && !exploded[i - 1][j] && grid[i - 1][j] <= grid[i][j] {
            exploded[i - 1][j] = true;
            q.push_back((i - 1, j));
        }
        if i != h - 1 && !exploded[i + 1][j] && grid[i + 1][j] <= grid[i][j] {
            exploded[i + 1][j] = true;
            q.push_back((i + 1, j));
        }
        if j != 0 && !exploded[i][j - 1] && grid[i][j - 1] <= grid[i][j] {
            exploded[i][j - 1] = true;
            q.push_back((i, j - 1));
        }
        if j != w - 1 && !exploded[i][j + 1] && grid[i][j + 1] <= grid[i][j] {
            exploded[i][j + 1] = true;
            q.push_back((i, j + 1));
        }
    }

    true_count(exploded) - baseline
}

fn main() {
    let grid: Vec<Vec<u8>> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().bytes().map(|x| x - b'0').collect())
        .collect();

    let h = grid.len();
    let w = grid[0].len();
    let mut exploded: Vec<Vec<bool>> = vec![vec![false; w]; h];

    for _ in 0..3 {
        let first = (0..h)
            .cartesian_product(0..w)
            .filter(|&(i, j)| !exploded[i][j])
            .max_by_key(|ij| {
                let mut tmp = exploded.clone();
                explosion_yield(&grid, &mut tmp, *ij)
            })
            .unwrap();

        explosion_yield(&grid, &mut exploded, first);
    }

    println!("{}", true_count(&exploded));
}
