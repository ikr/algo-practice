use std::io::{BufRead, stdin};

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

    eprintln!("{heads:?}");
}
