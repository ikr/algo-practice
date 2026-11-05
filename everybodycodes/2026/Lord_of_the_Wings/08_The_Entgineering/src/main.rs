use std::{
    io::{BufRead, stdin},
    iter::successors,
};

fn transpose<T>(grid: Vec<Vec<T>>) -> Vec<Vec<T>> {
    let h = grid[0].len();
    let mut iters: Vec<_> = grid.into_iter().map(|n| n.into_iter()).collect();
    (0..h)
        .map(|_| {
            iters
                .iter_mut()
                .map(|n| n.next().unwrap())
                .collect::<Vec<T>>()
        })
        .collect()
}

fn rotate_90_cc<T>(grid: Vec<Vec<T>>) -> Vec<Vec<T>> {
    let mut result = transpose(grid);
    result.reverse();
    result
}

fn diag_alley(grid: &[Vec<u8>], head: (usize, usize)) -> Vec<u8> {
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

    heads.into_iter().map(|h| diag_alley(&grid, h)).collect()
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

    let grid1 = rotate_90_cc(grid0.clone());
    let mut result: usize = 0;

    for g in [&grid0, &grid1] {
        let xss = all_diag_alleys(g);

        let yss: Vec<Vec<u8>> = xss
            .iter()
            .cloned()
            .map(|xs| xs.into_iter().rev().collect())
            .collect();

        let one = xss.into_iter().map(lit_count).sum::<usize>();
        let two = yss.into_iter().map(lit_count).sum::<usize>();
        eprintln!("one:{one} two:{two}");

        result += one;
        result += two;
    }

    {
        let xss: Vec<Vec<_>> = grid0
            .into_iter()
            .map(|row| row.into_iter().filter(|&x| x != 0).collect::<Vec<_>>())
            .collect();

        let yss: Vec<Vec<u8>> = xss
            .iter()
            .cloned()
            .map(|xs| xs.into_iter().rev().collect())
            .collect();

        let one = xss.into_iter().map(lit_count).sum::<usize>();
        let two = yss.into_iter().map(lit_count).sum::<usize>();
        eprintln!("one:{one} two:{two}");

        result += one;
        result += two;
    }

    println!("{result}");
}
