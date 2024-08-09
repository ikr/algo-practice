use regex::Regex;
use std::io::{self, BufRead};

fn parse_fact(src: &str) -> (String, [i8; 5]) {
    let re = Regex::new(r"^([A-Z][a-z]+): capacity (-?\d+), durability (-?\d+), flavor (-?\d+), texture (-?\d+), calories (-?\d+)$").unwrap();
    let caps = re.captures(src).unwrap();
    (
        caps[1].to_string(),
        caps.iter()
            .skip(2)
            .map(|x| x.unwrap().as_str().parse::<i8>().unwrap())
            .collect::<Vec<_>>()
            .try_into()
            .unwrap(),
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
