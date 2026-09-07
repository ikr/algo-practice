use std::{collections::HashSet, io::BufRead};

use itertools::Itertools;

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i32, i32);

impl Crd {
    fn halfway_to(self, dst: Crd) -> Crd {
        Crd((self.0 + dst.0) / 2, (self.1 + dst.1) / 2)
    }

    fn neighs(self) -> Vec<Crd> {
        vec![
            Crd(self.0, self.1 + 1),
            Crd(self.0 + 1, self.1),
            Crd(self.0, self.1 - 1),
            Crd(self.0 - 1, self.1),
        ]
    }

    fn adjacent_wrt(self, beacons: &[Crd]) -> Vec<Crd> {
        beacons
            .iter()
            .map(|b| self.halfway_to(*b))
            .unique()
            .collect()
    }
}

struct BeetlesDfs {
    beacons: Vec<Crd>,
    visited: HashSet<Crd>,
}

impl BeetlesDfs {
    fn new(beacons: Vec<Crd>) -> Self {
        Self {
            beacons,
            visited: HashSet::new(),
        }
    }

    fn recur(&mut self, p: Crd) {
        self.visited.insert(p);
        for q in p.adjacent_wrt(&self.beacons) {
            if !self.visited.contains(&q) {
                self.recur(q);
            }
        }
    }
}

fn decode_input_line_crd(line: &str) -> Crd {
    let i = line.find('[').unwrap();
    let j = line.find(']').unwrap();

    let (x, y) = line[i + 1..j]
        .split(',')
        .map(|s| s.parse().unwrap())
        .collect_tuple()
        .unwrap();

    Crd(x, y)
}

fn main() {
    let lines: Vec<String> = std::io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap())
        .collect();

    let start = decode_input_line_crd(&lines[0]);

    let beacons: Vec<Crd> = lines[1..]
        .iter()
        .map(|line| decode_input_line_crd(line))
        .collect();

    let mut dfs = BeetlesDfs::new(beacons.clone());
    dfs.recur(start);

    let fireflies: HashSet<Crd> = dfs
        .visited
        .iter()
        .flat_map(|p| p.neighs().into_iter().filter(|q| !dfs.visited.contains(q)))
        .collect();

    println!("{}", fireflies.len());
}
