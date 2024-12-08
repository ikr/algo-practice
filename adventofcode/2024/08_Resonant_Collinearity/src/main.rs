use std::{
    collections::{HashMap, HashSet},
    io::{self, BufRead},
};

use itertools::Itertools;

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i8, i8);

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

impl std::ops::Sub<Crd> for Crd {
    type Output = Crd;

    fn sub(self, o: Crd) -> Crd {
        Crd(self.0 - o.0, self.1 - o.1)
    }
}

impl Crd {
    fn antinodes_wrt(&self, h: i8, w: i8, other: Crd) -> Vec<Crd> {
        let in_bounds = |p: Crd| {
            let Crd(ro, co) = p;
            0 <= ro && ro < h && 0 <= co && co < w
        };

        let delta = other - *self;
        let mut result = vec![];
        let mut cur = other;
        while in_bounds(cur + delta) {
            cur = cur + delta;
            result.push(cur);
        }
        result
    }
}

fn coordinates_by_symbol(grid: &[Vec<char>]) -> HashMap<char, Vec<Crd>> {
    grid.iter()
        .enumerate()
        .flat_map(|(i, row)| {
            row.iter().enumerate().filter_map(move |(j, &cell)| {
                if cell != '.' {
                    Some((cell, Crd(i as i8, j as i8)))
                } else {
                    None
                }
            })
        })
        .fold(HashMap::new(), |mut map, (x, crd)| {
            map.entry(x).or_default().push(crd);
            map
        })
}

fn main() {
    let grid: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let h = grid.len() as i8;
    let w = grid[0].len() as i8;

    let mut antinodes: HashSet<Crd> = HashSet::new();

    for (_, crds) in coordinates_by_symbol(&grid) {
        for pq in crds.into_iter().combinations(2) {
            let [p, q] = pq.try_into().unwrap();
            antinodes.insert(p);
            antinodes.insert(q);
            for crd in [p.antinodes_wrt(h, w, q), q.antinodes_wrt(h, w, p)].concat() {
                antinodes.insert(crd);
            }
        }
    }

    println!("{}", antinodes.len());
}
