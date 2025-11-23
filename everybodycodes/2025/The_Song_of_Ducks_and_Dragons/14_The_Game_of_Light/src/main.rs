use std::io::{BufRead, stdin};

const SZ: usize = 34;
const ROUNDS: usize = 1_000_000_000;

fn grid_dimentions(grid: &[Vec<bool>]) -> (usize, usize) {
    (grid.len(), grid[0].len())
}

fn neighs_count(grid: &[Vec<bool>], i: usize, j: usize) -> usize {
    let (h, w) = grid_dimentions(grid);
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
    let (h, w) = grid_dimentions(&grid);
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

fn confirm_center_piece_match(grid: &[Vec<bool>], center_piece: &[Vec<bool>]) -> bool {
    let (h, w) = grid_dimentions(grid);
    let (hh, ww) = grid_dimentions(center_piece);
    let dh = (h - hh) / 2;
    let dw = (w - ww) / 2;

    grid[dh..dh + hh]
        .iter()
        .zip(center_piece)
        .all(|(row_a, row_b)| row_a[dw..dw + ww] == *row_b)
}

fn main() {
    let special_center_piece: Vec<Vec<bool>> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().bytes().map(|x| x == b'#').collect())
        .collect();

    let mut grid = vec![vec![false; SZ]; SZ];

    assert!(!confirm_center_piece_match(&grid, &special_center_piece));

    assert!(confirm_center_piece_match(
        &special_center_piece,
        &special_center_piece
    ));

    for _ in 0..125 {
        grid = next_gen(grid);
    }
    assert!(confirm_center_piece_match(&grid, &special_center_piece));
    eprintln!("Yep");
}
