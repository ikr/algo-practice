use regex::Regex;
use std::io::{BufRead, stdin};

fn parse_initial_holding(s: &str) -> (String, i32) {
    let ps: Vec<_> = s.split(" HAS ").collect();
    (ps[0].to_string(), ps[1].parse().unwrap())
}

fn parse_movement(s: &str) -> (String, String, i32) {
    let re = Regex::new(r"^FROM (\w+) TO (\w+) AMT (\d+)$").unwrap();
    let caps = re.captures(s).unwrap();
    (
        caps[1].to_string(),
        caps[2].to_string(),
        caps[3].parse().unwrap(),
    )
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|s| s.unwrap()).collect();
    let isep: usize = lines.iter().position(|s| s.is_empty()).unwrap();

    let initial_holdings: Vec<_> = lines[..isep]
        .iter()
        .map(|s| parse_initial_holding(s))
        .collect();

    let movements: Vec<_> = lines[isep + 1..]
        .iter()
        .map(|s| parse_movement(s))
        .collect();

    eprintln!("{:?}\n{:?}", initial_holdings, movements);
}
