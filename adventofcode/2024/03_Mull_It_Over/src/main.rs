use regex::Regex;
use std::io::{self, Read};

fn parse_token(s: &str) -> (i32, i32) {
    let xs: Vec<i32> = s
        .strip_prefix("mul(")
        .and_then(|s| s.strip_suffix(")"))
        .unwrap()
        .split(",")
        .map(|x| x.parse().unwrap())
        .collect();
    (xs[0], xs[1])
}

fn main() {
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();

    let tokens: Vec<_> = Regex::new(r"mul\(\d+,\d+\)")
        .unwrap()
        .find_iter(&input)
        .map(|x| parse_token(x.as_str()))
        .collect();

    let result: i32 = tokens.iter().map(|(x, y)| x * y).sum();
    println!("{}", result);
}
