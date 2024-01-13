use regex::Regex;
use std::{
    collections::{BTreeMap, BTreeSet},
    io::{self, BufRead},
};

#[derive(Clone, Debug, PartialEq, Eq, PartialOrd, Ord)]
struct Coord(i32, i32);

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
    (y1..=y2).map(|y| Coord(x, y)).collect()
}

fn parse_horizontal_line(src: &str) -> Vec<Coord> {
    assert!(src.starts_with('y'));
    let (y, x1, x2) = parse_tri(src);
    (x1..=x2).map(|x| Coord(x, y)).collect()
}

fn parse_src_line(src: &str) -> Vec<Coord> {
    if src.starts_with('x') {
        parse_vertical_line(src)
    } else {
        parse_horizontal_line(src)
    }
}

#[derive(Debug)]
struct Reservoir {
    clay: BTreeSet<Coord>,
    clay_xs_by_y: BTreeMap<i32, BTreeSet<i32>>,
}

impl Reservoir {
    fn new() -> Self {
        Reservoir {
            clay: BTreeSet::new(),
            clay_xs_by_y: BTreeMap::new(),
        }
    }

    fn register_clay(&mut self, xy: Coord) {
        let Coord(x, y) = xy;
        self.clay.insert(xy);
        self.clay_xs_by_y.entry(x).or_default().insert(y);
    }
}

fn main() {
    let mut rvr = Reservoir::new();

    for line in io::stdin().lock().lines() {
        for xy in parse_src_line(&line.unwrap()) {
            rvr.register_clay(xy);
        }
    }

    eprintln!("{:?}", rvr);
}
