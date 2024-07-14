use std::io::{self, BufRead};

use regex::Regex;

fn parse_relative_happiness(src: &str) -> (String, String, i32) {
    let re = Regex::new(
        r"^([A-Z][a-z]+) would (gain|lose) (\d+) happiness units by sitting next to ([A-Z][a-z]+).$",
    )
    .unwrap();

    let caps = re.captures(src).unwrap();
    let u: String = caps[1].to_string();
    let v: String = caps[4].to_string();

    let sign = if caps[2] == *"lose" { -1 } else { 1 };
    let x: i32 = caps[3].parse().unwrap();

    (u, v, sign * x)
}

fn main() {
    let facts: Vec<_> = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_relative_happiness(&line.unwrap()))
        .collect();
    eprintln!("{:?}", facts);
}
