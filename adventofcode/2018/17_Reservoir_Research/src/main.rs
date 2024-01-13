use regex::Regex;
use std::io::{self, BufRead};
use std::ops;

#[derive(Clone, Debug)]
struct Coord(i32, i32);

impl ops::Add for Coord {
    type Output = Self;

    fn add(self, rhs: Self) -> Self {
        Self(self.0 + rhs.0, self.1 + rhs.1)
    }
}

fn parse_tri(src: &str) -> (i32, i32, i32) {
    let re = Regex::new(r"^[xy]=(\d+), [xy]=(\d+)\.\.(\d+)$").unwrap();
    let caps = re.captures(src).unwrap();
    (
        caps[1].parse().unwrap(),
        caps[2].parse().unwrap(),
        caps[3].parse().unwrap(),
    )
}

fn main() {
    for line in io::stdin().lock().lines() {
        eprintln!("{:?}", parse_tri(&line.unwrap()))
    }
}
