use regex::Regex;
use std::{
    collections::{BTreeMap, BTreeSet, HashMap},
    io::{self, BufRead},
};

#[derive(Copy, Clone, Debug, PartialEq, Eq, PartialOrd, Ord, Hash)]
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
    assert!(y1 <= y2);
    (y1..=y2).map(|y| Coord(x, y)).collect()
}

fn parse_horizontal_line(src: &str) -> Vec<Coord> {
    assert!(src.starts_with('y'));
    let (y, x1, x2) = parse_tri(src);
    assert!(x1 <= x2);
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

        let Coord(x, y) = xy;
        x_lo <= x && x <= x_hi && *y_lo <= y && y <= *y_hi
    }

    fn neigh_wall_ys(&self, xy0: Coord) -> Option<(i32, i32)> {
        let Coord(x0, y0) = xy0;
        let row = self.clay_xs_by_y.get(&y0)?;
        let before = row.range(..x0).last()?;
        let after = row.range(x0..).next()?;
        assert!(*before < x0 && x0 < *after);
        Some((*before, *after))
    }

    fn contained(&self, memo: &mut HashMap<Coord, bool>, xy: Coord) -> bool {
        if memo.contains_key(&xy) {
            return *memo.get(&xy).unwrap();
        }

        if let Some((a, b)) = self.neigh_wall_ys(xy) {
            for x in a + 1..b {
                let v = Coord(x, xy.1 + 1);
                if !self.clay.contains(&v) && !self.contained(memo, v) {
                    return false;
                }
            }
            memo.insert(xy, true);
            true
        } else {
            memo.insert(xy, false);
            false
        }
    }

    fn solve_part_1(&self) -> i32 {
        let mut contained_memo: HashMap<Coord, bool> = HashMap::new();
        self.contained(&mut contained_memo, Coord(500, 3));
        eprintln!("{:?}", contained_memo);
        -1
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
    assert!(rvr.in_scope(Coord(500, 13)));
    assert!(!rvr.in_scope(Coord(500, 14)));

    assert!(rvr.neigh_wall_ys(Coord(500, 0)).is_none());
    assert!(rvr.neigh_wall_ys(Coord(500, 1)).is_none());
    assert!(rvr.neigh_wall_ys(Coord(502, 9)).is_none());
    assert!(rvr.neigh_wall_ys(Coord(500, 2)) == Some((498, 506)));
    assert!(rvr.neigh_wall_ys(Coord(499, 12)) == Some((498, 504)));
    assert!(rvr.neigh_wall_ys(Coord(503, 11)) == Some((498, 504)));

    println!("{}", rvr.solve_part_1());
}
