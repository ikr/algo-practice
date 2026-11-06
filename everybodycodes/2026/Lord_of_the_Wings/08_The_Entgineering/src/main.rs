use std::{
    io::{BufRead, stdin},
    iter::successors,
};

fn reverse_rows<T>(mut grid: Vec<Vec<T>>) -> Vec<Vec<T>> {
    for row in &mut grid {
        row.reverse();
    }
    grid
}

fn diag_alley<T: Copy>(grid: &[Vec<T>], head: (usize, usize)) -> Vec<T> {
    let height = grid.len();
    let width = grid[0].len();

    successors(Some(head), |(i, j)| {
        (i + 1 < height && j + 1 < width).then_some((i + 1, j + 1))
    })
    .map(|(i, j)| grid[i][j])
    .collect()
}

fn all_diag_alleys(grid: &[Vec<u8>]) -> Vec<Vec<u8>> {
    let left_top_column: usize = grid[0].iter().position(|&x| x != 0).unwrap();
    let left_row = left_top_column;
    let right_top_column: usize = grid[0].iter().rposition(|&x| x != 0).unwrap();

    let heads: Vec<(usize, usize)> = (left_top_column..=right_top_column)
        .step_by(2)
        .map(|j| (0, j))
        .chain((1..=left_row).map(|i| (i, left_top_column - i)))
        .collect();

    heads.into_iter().map(|h| diag_alley(grid, h)).collect()
}

fn all_horz_alleys(grid: &[Vec<u8>]) -> Vec<Vec<u8>> {
    grid.iter()
        .map(|row| row.iter().copied().filter(|&x| x != 0).collect::<Vec<_>>())
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
    let grid0: Vec<Vec<u8>> = stdin()
        .lock()
        .lines()
        .map(|line| {
            line.unwrap()
                .bytes()
                .map(|x| if x == b'.' { 0 } else { x - b'0' })
                .collect()
        })
        .collect();

    let grid1 = reverse_rows(grid0.clone());
    let mut result: usize = 0;

    for g in [&grid0, &grid1] {
        let xss = all_diag_alleys(g);
        result += xss.clone().into_iter().map(lit_count).sum::<usize>();
        result += reverse_rows(xss).into_iter().map(lit_count).sum::<usize>();
    }

    let xss = all_horz_alleys(&grid0);
    result += xss.clone().into_iter().map(lit_count).sum::<usize>();
    result += reverse_rows(xss).into_iter().map(lit_count).sum::<usize>();

    println!("{result}");
}
