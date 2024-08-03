use regex::Regex;
use std::io::{self, BufRead};

#[derive(Debug)]
struct Mobility {
    velocity: i64,
    flight_seconds: i64,
    rest_seconds: i64,
}

fn parse_fact(src: &str) -> (String, Mobility) {
    let re = Regex::new(r"^([A-Z][a-z]+) can fly (\d+) km/s for (\d+) seconds, but then must rest for (\d+) seconds.$").unwrap();
    let caps = re.captures(src).unwrap();
    let velocity: i64 = caps[2].parse().unwrap();
    let flight_seconds: i64 = caps[3].parse().unwrap();
    let rest_seconds: i64 = caps[4].parse().unwrap();
    (
        caps[1].to_string(),
        Mobility {
            velocity,
            flight_seconds,
            rest_seconds,
        },
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
