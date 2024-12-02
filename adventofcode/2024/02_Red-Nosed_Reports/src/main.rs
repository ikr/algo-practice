use std::io::{self, BufRead};

fn parse_line(s: &str) -> Vec<i32> {
    s.split_whitespace().map(|x| x.parse().unwrap()).collect()
}

fn is_safe(xs: &[i32]) -> bool {
    (xs.windows(2).all(|w| w[0] < w[1]) || xs.windows(2).all(|w| w[0] > w[1]))
        && xs.windows(2).all(|w| w[0].abs_diff(w[1]) <= 3)
}

fn main() {
    let grid: Vec<Vec<i32>> = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_line(&line.unwrap()))
        .collect();

    let result = grid.iter().filter(|row| is_safe(row)).count();
    eprintln!("{:?}", result);
}
