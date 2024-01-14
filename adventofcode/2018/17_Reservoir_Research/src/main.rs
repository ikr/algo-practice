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
        self.clay_xs_by_y.entry(y).or_default().insert(x);
    }

    fn in_scope(&self, xy: Coord) -> bool {
        let x_lo = self.clay.first().unwrap().0;
        let x_hi = self.clay.last().unwrap().0;
        let y_lo = self.clay_xs_by_y.first_key_value().unwrap().0;
        let y_hi = self.clay_xs_by_y.last_key_value().unwrap().0;

        eprintln!("x_lo: {}, x_hi: {}", x_lo, x_hi);
        eprintln!("y_lo: {}, y_hi: {}", y_lo, y_hi);

        let Coord(x, y) = xy;
        x_lo <= x && x <= x_hi && *y_lo <= y && y <= *y_hi
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
    assert!(!rvr.in_scope(Coord(500, 0)));
    assert!(rvr.in_scope(Coord(500, 1)));
}
