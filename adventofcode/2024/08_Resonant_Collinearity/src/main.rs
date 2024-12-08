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
    fn antinode_wrt(&self, other: Crd) -> Crd {
        let delta = other - *self;
        other + delta
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

    let in_bounds = |crd: Crd| {
        let h = grid.len() as i8;
        let w = grid[0].len() as i8;
        let Crd(ro, co) = crd;
        0 <= ro && ro < h && 0 <= co && co < w
    };

    // let cell_at = |crd: Crd| {
    //     assert!(in_bounds(crd));
    //     let Crd(ro, co) = crd;
    //     grid[ro as usize][co as usize]
    // };

    let mut antinodes: HashSet<Crd> = HashSet::new();

    for (_, crds) in coordinates_by_symbol(&grid) {
        for pq in crds.into_iter().combinations(2) {
            let [p, q] = pq.try_into().unwrap();
            for crd in [p.antinode_wrt(q), q.antinode_wrt(p)] {
                if in_bounds(crd) {
                    antinodes.insert(crd);
                }
            }
        }
    }

    println!("{}", antinodes.len());
}
