use regex::Regex;
use std::io::{self, BufRead};

fn parse_fact(src: &str) -> (String, i64, i64, i64) {
    let re = Regex::new(r"^([A-Z][a-z]+) can fly (\d+) km/s for (\d+) seconds, but then must rest for (\d+) seconds.$").unwrap();
    let caps = re.captures(src).unwrap();
    (
        caps[1].to_string(),
        caps[2].parse().unwrap(),
        caps[3].parse().unwrap(),
        caps[4].parse().unwrap(),
    )
}

fn main() {
    let facts: Vec<_> = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_fact(&line.unwrap()))
        .collect();

    eprintln!("{:?}", facts);
}
