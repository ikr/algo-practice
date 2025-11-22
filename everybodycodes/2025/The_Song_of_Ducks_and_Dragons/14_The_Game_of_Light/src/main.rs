use std::io::{BufRead, stdin};

fn neighs_count(grid: &[Vec<bool>], i: usize, j: usize) -> usize {
    let h = grid.len();
    let w = grid[0].len();
    [
        (i != 0 && j != 0, i.saturating_sub(1), j.saturating_sub(1)),
        (i != 0 && j != w - 1, i.saturating_sub(1), j + 1),
        (i != h - 1 && j != w - 1, i + 1, j + 1),
        (i != h - 1 && j != 0, i + 1, j.saturating_sub(1)),
    ]
    .into_iter()
    .filter(|&(p, ii, jj)| p && grid[ii][jj])
    .count()
}

fn next_gen(grid: Vec<Vec<bool>>) -> Vec<Vec<bool>> {
    let h = grid.len();
    let w = grid[0].len();
    let mut result = vec![vec![false; w]; h];

    for i in 0..h {
        for j in 0..w {
            let v = if grid[i][j] { 1 } else { 0 };
            result[i][j] = neighs_count(&grid, i, j) % 2 == v;
        }
    }

    result
}

fn true_count(xss: &[Vec<bool>]) -> usize {
    xss.iter()
        .map(|row| row.iter().filter(|x| **x).count())
        .sum()
}

fn main() {
    let mut grid: Vec<Vec<bool>> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().bytes().map(|x| x == b'#').collect())
        .collect();

    let mut result = 0;
    for _ in 0..2025 {
        grid = next_gen(grid);
        result += true_count(&grid);
    }
    println!("{result}");
}
