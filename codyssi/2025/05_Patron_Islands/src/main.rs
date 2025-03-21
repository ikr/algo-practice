use std::io::{self, BufRead};

fn parse_line(s: &str) -> (i32, i32) {
    let parts: Vec<_> = s
        .strip_prefix('(')
        .and_then(|t| t.strip_suffix(')'))
        .unwrap()
        .split(", ")
        .collect();

    (parts[0].parse().unwrap(), parts[1].parse().unwrap())
}

fn main() {
    let xys: Vec<(i32, i32)> = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_line(&line.unwrap()))
        .collect();

    let ds: Vec<i32> = xys.into_iter().map(|(x, y)| x.abs() + y.abs()).collect();
    let result = ds.iter().max().unwrap() - ds.iter().min().unwrap();
    println!("{}", result);
}
