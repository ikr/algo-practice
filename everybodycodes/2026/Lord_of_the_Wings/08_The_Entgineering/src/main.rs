use std::{
    io::{BufRead, stdin},
    iter::successors,
};

fn alley(grid: &[Vec<u8>], head: (usize, usize)) -> Vec<u8> {
    let height = grid.len();
    let width = grid[0].len();

    successors(Some(head), |(i, j)| {
        (i + 1 < height && j + 1 < width).then_some((i + 1, j + 1))
    })
    .map(|(i, j)| grid[i][j])
    .collect()
}

fn lit_count(xs: Vec<u8>) -> usize {
    xs.into_iter()
        .fold((0, 0u8), |(r, hi), x| {
            (
                if x > hi { r + 1 } else { r },
                (hi.saturating_sub(1).max(x.saturating_sub(1))),
            )
        })
        .0
}

fn main() {
    let grid: Vec<Vec<u8>> = stdin()
        .lock()
        .lines()
        .map(|line| {
            line.unwrap()
                .bytes()
                .map(|x| if x == b'.' { 0 } else { x - b'0' })
                .collect()
        })
        .collect();

    let left_top_column: usize = grid[0].iter().position(|&x| x != 0).unwrap();
    let left_row = left_top_column;
    let right_top_column: usize = grid[0].iter().rposition(|&x| x != 0).unwrap();

    let heads: Vec<(usize, usize)> = (left_top_column..=right_top_column)
        .step_by(2)
        .map(|j| (0, j))
        .chain((1..=left_row).map(|i| (i, left_top_column - i)))
        .collect();

    let result: Vec<_> = heads
        .into_iter()
        .map(|h| alley(&grid, h))
        .map(lit_count)
        .collect();

    println!("{}", result.into_iter().sum::<usize>());
}
