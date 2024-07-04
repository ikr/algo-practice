use std::io::{self, BufRead};

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

fn main() {
    let grid: Vec<Vec<u8>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().into_bytes())
        .collect();

    eprintln!("{:?}", waypoints(&grid));
}
