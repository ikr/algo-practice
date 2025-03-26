use std::io::{self, BufRead};

fn transpose<T>(grid: Vec<Vec<T>>) -> Vec<Vec<T>> {
    assert!(!grid.is_empty());
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

fn min_row_sum(rows: &[Vec<u16>]) -> u16 {
    rows.iter().map(|xs| xs.iter().sum::<u16>()).min().unwrap()
}

fn main() {
    let grid: Vec<Vec<u16>> = io::stdin()
        .lock()
        .lines()
        .map(|line| {
            line.unwrap()
                .split_whitespace()
                .map(|s| s.parse::<u16>().unwrap())
                .collect::<Vec<_>>()
        })
        .collect();

    let result = min_row_sum(&grid).min(min_row_sum(&transpose(grid)));
    println!("{}", result);
}
