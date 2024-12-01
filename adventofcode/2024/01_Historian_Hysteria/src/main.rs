use std::io::{self, BufRead};

fn main() {
    let grid: Vec<(i32, i32)> = io::stdin()
        .lock()
        .lines()
        .map(|line| {
            let parts: Vec<i32> = line
                .unwrap()
                .split_whitespace()
                .map(|x| x.parse().unwrap())
                .collect();
            (parts[0], parts[1])
        })
        .collect();

    let mut xs: Vec<i32> = grid.iter().map(|(x, _)| *x).collect();
    xs.sort();

    let mut ys: Vec<i32> = grid.iter().map(|(_, y)| *y).collect();
    ys.sort();

    let result: u32 = xs
        .into_iter()
        .zip(ys.into_iter())
        .map(|(x, y)| x.abs_diff(y))
        .sum();

    println!("{}", result);
}
