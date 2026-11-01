use itertools::Itertools;
use std::{
    collections::{HashSet, VecDeque},
    io::{BufRead, stdin},
};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i32, i32);

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

impl Crd {
    fn adjacent(self) -> Vec<Self> {
        (-1..=1)
            .cartesian_product(-1..=1)
            .filter_map(|(i, j)| (i != 0 || j != 0).then_some(self + Crd(i, j)))
            .collect()
    }

    fn is_in_grid(self, height: i32, width: i32) -> bool {
        0 <= self.0 && self.0 < height && 0 <= self.1 && self.1 < width
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let height = lines.len() as i32;
    let width = lines[0].len() as i32;

    let dark_cells: HashSet<Crd> = lines
        .into_iter()
        .enumerate()
        .flat_map(|(i, row)| {
            row.bytes()
                .enumerate()
                .filter_map(|(j, x)| (x == b'1').then_some(Crd(i as i32, j as i32)))
                .collect::<Vec<_>>()
        })
        .collect();

    let center = Crd(height / 2, width / 2);

    let mut land: HashSet<Crd> = HashSet::from([center]);
    let mut q: VecDeque<Crd> = VecDeque::from([center]);

    while let Some(u) = q.pop_front() {
        for v in u
            .adjacent()
            .into_iter()
            .filter(|a| a.is_in_grid(height, width))
        {
            if !land.contains(&v)
                && v.adjacent()
                    .into_iter()
                    .filter(|a| dark_cells.contains(a) || land.contains(a))
                    .count()
                    >= 5
            {
                land.insert(v);
                q.push_back(v);
            }
        }
    }

    let initial_sand: Vec<Crd> = land
        .iter()
        .cloned()
        .filter(|&a| a.adjacent().into_iter().any(|b| !land.contains(&b)))
        .collect();

    let mut sand: HashSet<Crd> = initial_sand.iter().cloned().collect();
    q.extend(initial_sand);

    while let Some(u) = q.pop_front() {
        for v in u.adjacent().into_iter().filter(|a| land.contains(a)) {
            if !sand.contains(&v)
                && v.adjacent()
                    .into_iter()
                    .filter(|a| sand.contains(a))
                    .count()
                    >= 5
            {
                sand.insert(v);
                q.push_back(v);
            }
        }
    }

    println!("{}", sand.len());
}
