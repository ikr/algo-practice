use std::{
    collections::{HashMap, VecDeque},
    io::{self, BufRead},
};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i32, i32);

fn min_distance(grid: &[Vec<u8>], source: Crd, destinations: &[Crd]) -> u32 {
    let in_bounds = |crd: Crd| -> bool {
        0 <= crd.0 && crd.0 < grid.len() as i32 && 0 <= crd.1 && crd.1 < grid[0].len() as i32
    };

    let cell_at = |crd: Crd| -> u8 { grid[crd.0 as usize][crd.1 as usize] };

    let adjacent = |crd: Crd| -> Vec<Crd> {
        let Crd(ro, co) = crd;
        [
            Crd(ro - 1, co),
            Crd(ro, co + 1),
            Crd(ro + 1, co),
            Crd(ro, co - 1),
        ]
        .into_iter()
        .filter(|crd| in_bounds(*crd) && cell_at(*crd) != b'#' && cell_at(*crd) != b'~')
        .collect()
    };

    let mut distances: HashMap<Crd, u32> = HashMap::from([(source, 0)]);
    let mut q: VecDeque<Crd> = VecDeque::from([source]);

    while let Some(u) = q.pop_front() {
        for v in adjacent(u) {
            if !distances.contains_key(&v) {
                distances.insert(v, distances[&u] + 1);
                q.push_back(v);
            }
        }
    }

    destinations.iter().map(|crd| distances[crd]).min().unwrap()
}

fn main() {
    let grid: Vec<Vec<u8>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().bytes().collect())
        .collect();

    let source_column = grid[0].iter().position(|&x| x == b'.').unwrap();
    let source = Crd(0, source_column as i32);

    let crds_by_node = {
        let mut result: HashMap<u8, Vec<Crd>> = HashMap::from([(b'@', vec![source])]);
        for (i, row) in grid.iter().enumerate() {
            for (j, &cell) in row.iter().enumerate() {
                if cell.is_ascii_uppercase() {
                    result
                        .entry(cell)
                        .or_default()
                        .push(Crd(i as i32, j as i32));
                }
            }
        }
        result
    };

    let n = crds_by_node.len();
    let mut g: Vec<Vec<u32>> = vec![vec![10u32.pow(7); n]; n];
}
