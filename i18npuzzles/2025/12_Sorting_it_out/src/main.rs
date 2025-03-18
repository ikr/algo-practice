use std::io::{self, BufRead};

use regex::Regex;

fn parse_line(s: &str) -> (String, String, u64) {
    let re = Regex::new(r"^(.+), (.+): (\d+)$").unwrap();
    let caps = re.captures(s).unwrap();
    (
        caps[1].to_string(),
        caps[2].to_string(),
        caps[3].parse().unwrap(),
    )
}

fn main() {
    let lines: Vec<_> = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_line(&line.unwrap()))
        .collect();

    eprintln!("{:?}", lines);
}
