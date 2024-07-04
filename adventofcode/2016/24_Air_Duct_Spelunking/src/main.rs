use std::{
    collections::{HashSet, VecDeque},
    io::{self, BufRead},
};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i32, i32);

fn max_waypoint_index(grid: &[Vec<u8>]) -> usize {
    let b: u8 = grid.iter().fold(0, |acc, row| {
        acc.max(row.iter().fold(0, |sub, x| sub.max(*x)))
    });
    (b - b'0') as usize
}

fn waypoints(grid: &[Vec<u8>]) -> Vec<Crd> {
    let mut result: Vec<Crd> = vec![Crd(-1, -1); max_waypoint_index(grid) + 1];

    for (ro, row) in grid.iter().enumerate() {
        for (co, x) in row.iter().enumerate() {
            if x.is_ascii_digit() {
                let index = (x - b'0') as usize;
                result[index] = Crd(ro as i32, co as i32);
            }
        }
    }

    assert!(result.iter().all(|crd| *crd != Crd(-1, -1)));
    result
}

fn distance_between(grid: &[Vec<u8>], a: Crd, b: Crd) -> i32 {
    let mut seen: HashSet<Crd> = HashSet::from([a]);
    let mut q: VecDeque<(Crd, i32)> = VecDeque::from([(a, 0)]);

    while let Some((u, d)) = q.pop_front() {
        let Crd(r0, c0) = u;
        for (r, c) in [(r0 - 1, c0), (r0, c0 + 1), (r0 + 1, c0), (r0, c0 - 1)] {
            let x = grid[r as usize][c as usize];
            if x != b'#' && !seen.contains(&Crd(r, c)) {
                if Crd(r, c) == b {
                    return d + 1;
                }
                seen.insert(Crd(r, c));
                q.push_back((Crd(r, c), d + 1));
            }
        }
    }

    i32::MAX
}

fn main() {
    let grid: Vec<Vec<u8>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().into_bytes())
        .collect();

    let wps = waypoints(&grid);
    eprintln!("{:?}", wps);
    eprintln!("1 → 3: {}", distance_between(&grid, wps[0], wps[3]));
}
