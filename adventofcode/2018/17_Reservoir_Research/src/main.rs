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

fn parse_vertical_line(src: &str) -> Vec<Coord> {
    assert!(src.starts_with('x'));
    let (x, y1, y2) = parse_tri(src);
    (y1..=y2).into_iter().map(|y| Coord(x, y)).collect()
}

fn parse_horizontal_line(src: &str) -> Vec<Coord> {
    assert!(src.starts_with('y'));
    let (y, x1, x2) = parse_tri(src);
    (x1..=x2).into_iter().map(|x| Coord(x, y)).collect()
}

fn parse_src_line(src: &str) -> Vec<Coord> {
    if src.starts_with('x') {
        parse_vertical_line(src)
    } else {
        parse_horizontal_line(src)
    }
}

fn main() {
    for line in io::stdin().lock().lines() {
        eprintln!("{:?}", parse_src_line(&line.unwrap()))
    }
}
