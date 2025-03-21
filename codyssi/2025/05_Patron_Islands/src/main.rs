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

    let closest_to_origin = xys
        .iter()
        .min_by_key(|(x, y)| (x.abs() + y.abs(), x, y))
        .unwrap();

    let (a, b) = *closest_to_origin;
    let result = xys
        .iter()
        .filter(|xy| *xy != closest_to_origin)
        .map(|(x, y)| x.abs_diff(a) + y.abs_diff(b))
        .min()
        .unwrap();
    println!("{}", result);
}
