use std::{
    collections::{HashMap, VecDeque},
    io::{self, BufRead},
};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i8, i8);

fn main() {
    let grid: Vec<Vec<u8>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().bytes().collect())
        .collect();

    let in_bounds = |crd: Crd| -> bool {
        0 <= crd.0 && crd.0 < grid.len() as i8 && 0 <= crd.1 && crd.1 < grid[0].len() as i8
    };

    let cell_at = |crd: Crd| -> u8 { grid[crd.0 as usize][crd.1 as usize] };

    let crds_of = |x: u8| -> Vec<Crd> {
        let mut result = vec![];
        for (i, row) in grid.iter().enumerate() {
            for (j, cell) in row.iter().enumerate() {
                if *cell == x {
                    result.push(Crd(i as i8, j as i8));
                }
            }
        }
        result
    };

    let adjacent = |crd: Crd| -> Vec<Crd> {
        let Crd(ro, co) = crd;
        [
            Crd(ro - 1, co),
            Crd(ro, co + 1),
            Crd(ro + 1, co),
            Crd(ro, co - 1),
        ]
        .into_iter()
        .filter(|crd| in_bounds(*crd) && cell_at(*crd) != b'#')
        .collect()
    };

    let source_column = grid[0].iter().position(|&x| x == b'.').unwrap();
    let source = Crd(0, source_column as i8);
    let destinations = crds_of(b'H');

    let mut distances: HashMap<Crd, u8> = HashMap::from([(source, 0)]);
    let mut q: VecDeque<Crd> = VecDeque::from([source]);

    while let Some(u) = q.pop_front() {
        for v in adjacent(u) {
            if !distances.contains_key(&v) {
                distances.insert(v, distances[&u] + 1);
                q.push_back(v);
            }
        }
    }

    let result = destinations.iter().map(|crd| distances[crd]).min().unwrap() * 2;
    println!("{}", result);
}
