use std::{
    io::{BufRead, stdin},
    iter::successors,
};

type AlleyPs = Vec<(usize, usize)>;
type AlleySet = Vec<AlleyPs>;

const EMPTY: i8 = i8::MIN;

fn reverse_rows<T>(mut grid: Vec<Vec<T>>) -> Vec<Vec<T>> {
    for row in &mut grid {
        row.reverse();
    }
    grid
}

fn diag_alley(grid: &[Vec<i8>], head: (usize, usize)) -> Vec<i8> {
    let height = grid.len();
    let width = grid[0].len();

    successors(Some(head), |(i, j)| {
        (i + 1 < height && j + 1 < width).then_some((i + 1, j + 1))
    })
    .filter_map(|(i, j)| {
        let x = grid[i][j];
        (x != EMPTY).then_some(x)
    })
    .collect()
}

fn all_diag_alleys(grid: &[Vec<i8>]) -> Vec<Vec<i8>> {
    let left_top_column: usize = grid[0].iter().position(|&x| x != EMPTY).unwrap();
    let left_row = left_top_column;
    let right_top_column: usize = grid[0].iter().rposition(|&x| x != EMPTY).unwrap();

    let heads: Vec<(usize, usize)> = (left_top_column..=right_top_column)
        .step_by(2)
        .map(|j| (0, j))
        .chain((1..=left_row).map(|i| (i, left_top_column - i)))
        .collect();

    heads.into_iter().map(|h| diag_alley(grid, h)).collect()
}

fn all_horz_alleys(grid: &[Vec<i8>]) -> Vec<Vec<i8>> {
    grid.iter()
        .map(|row| {
            row.iter()
                .copied()
                .filter(|&x| x != EMPTY)
                .collect::<Vec<_>>()
        })
        .collect()
}

fn lit_count(xs: Vec<i8>) -> usize {
    xs.into_iter()
        .fold((0, 0i8), |(r, hi), x| {
            (if x > hi { r + 1 } else { r }, ((hi - 1).max(0).max(x - 1)))
        })
        .0
}

fn all_alley_sets(grid: &[Vec<i8>]) -> Vec<AlleySet> {
    todo!()
}

fn main() {
    let grid0: Vec<Vec<i8>> = stdin()
        .lock()
        .lines()
        .map(|line| {
            line.unwrap()
                .bytes()
                .map(|x| if x == b'.' { EMPTY } else { (x - b'0') as i8 })
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
