use regex::Regex;
use std::{
    collections::{BTreeMap, BTreeSet, HashMap, HashSet, VecDeque},
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
        let y_lo = self.clay_xs_by_y.first_key_value().unwrap().0;
        let y_hi = self.clay_xs_by_y.last_key_value().unwrap().0;

        *y_lo <= xy.1 && xy.1 <= *y_hi
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
        let mut visited: HashSet<Coord> = HashSet::new();
        visited.insert(Coord(500, 0));
        let mut q: VecDeque<Coord> = VecDeque::new();
        q.push_back(Coord(500, 0));

        while let Some(u) = q.pop_front() {
            let Coord(x0, y0) = u;
            if !self.clay.contains(&Coord(x0, y0 + 1))
                && !self.contained(&mut contained_memo, Coord(x0, y0 + 1))
            {
                if y0 < 3_000 {
                    visited.insert(Coord(x0, y0 + 1));
                    q.push_back(Coord(x0, y0 + 1));
                }
                continue;
            }
            if !self.clay.contains(&Coord(x0 - 1, y0)) && !visited.contains(&Coord(x0 - 1, y0)) {
                visited.insert(Coord(x0 - 1, y0));
                q.push_back(Coord(x0 - 1, y0));
            }
            if !self.clay.contains(&Coord(x0 + 1, y0)) && !visited.contains(&Coord(x0 + 1, y0)) {
                visited.insert(Coord(x0 + 1, y0));
                q.push_back(Coord(x0 + 1, y0));
            }
        }

        let mut contained: HashSet<Coord> = HashSet::new();
        for (u, yes) in contained_memo.iter() {
            if *yes {
                contained.insert(*u);
                q.push_back(*u);
            }
        }

        while let Some(u) = q.pop_front() {
            let Coord(x0, y0) = u;
            if !self.clay.contains(&Coord(x0 - 1, y0)) && !contained.contains(&Coord(x0 - 1, y0)) {
                contained.insert(Coord(x0 - 1, y0));
                q.push_back(Coord(x0 - 1, y0));
            }
            if !self.clay.contains(&Coord(x0 + 1, y0)) && !contained.contains(&Coord(x0 + 1, y0)) {
                contained.insert(Coord(x0 + 1, y0));
                q.push_back(Coord(x0 + 1, y0));
            }
        }

        (visited.into_iter().filter(|xy| self.in_scope(*xy)).count() + contained.len()) as i32
    }
}

fn main() {
    let mut rvr = Reservoir::new();

    for line in io::stdin().lock().lines() {
        for xy in parse_src_line(&line.unwrap()) {
            rvr.register_clay(xy);
        }
    }

    // assert!(!rvr.in_scope(Coord(500, 0)));
    // assert!(rvr.in_scope(Coord(500, 1)));
    // assert!(rvr.in_scope(Coord(500, 13)));
    // assert!(!rvr.in_scope(Coord(500, 14)));

    // assert!(rvr.neigh_wall_ys(Coord(500, 0)).is_none());
    // assert!(rvr.neigh_wall_ys(Coord(500, 1)).is_none());
    // assert!(rvr.neigh_wall_ys(Coord(502, 9)).is_none());
    // assert!(rvr.neigh_wall_ys(Coord(500, 2)) == Some((498, 506)));
    // assert!(rvr.neigh_wall_ys(Coord(499, 12)) == Some((498, 504)));
    // assert!(rvr.neigh_wall_ys(Coord(503, 11)) == Some((498, 504)));

    println!("{}", rvr.solve_part_1());
}
