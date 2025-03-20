use std::io::{self, BufRead};

fn parse_range(s: &str) -> (i32, i32) {
    let ab: Vec<i32> = s.split('-').map(|s| s.parse().unwrap()).collect();
    (ab[0], ab[1])
}

fn parse_line(s: &str) -> (i32, i32, i32, i32) {
    let ab: Vec<_> = s.split_ascii_whitespace().collect();
    let (a, b) = parse_range(ab[0]);
    let (c, d) = parse_range(ab[1]);
    (a, b, c, d)
}

fn main() {
    let lines: Vec<_> = io::stdin()
        .lock()
        .lines()
        .map(|s| parse_line(&s.unwrap()))
        .collect();

    let result: i32 = lines
        .into_iter()
        .map(|(a, b, c, d)| b - a + 1 + d - c + 1)
        .sum();
    println!("{}", result);
}
