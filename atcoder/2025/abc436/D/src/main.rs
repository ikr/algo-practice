use proconio::input;
use proconio::marker::Bytes;
use std::{
    collections::{HashMap, VecDeque},
    io::{BufWriter, Write, stdout},
};

fn is_warp(x: u8) -> bool {
    b'a' <= x && x <= b'z'
}

fn warp_index(x: u8) -> usize {
    assert!(is_warp(x));
    (x - b'a') as usize
}

fn crds_by_warp(grid: &[Vec<u8>]) -> Vec<Vec<(usize, usize)>> {
    let (h, w) = (grid.len(), grid[0].len());
    let mut result = vec![vec![]; 26];

    for i in 0..h {
        for j in 0..w {
            if is_warp(grid[i][j]) {
                result[warp_index(grid[i][j])].push((i, j));
            }
        }
    }

    result
}

fn adjacent(
    grid: &[Vec<u8>],
    cbw: &[Vec<(usize, usize)>],
    i: usize,
    j: usize,
) -> Vec<(usize, usize)> {
    let (h, w) = (grid.len(), grid[0].len());
    let mut result = vec![];

    if i != 0 && grid[i - 1][j] != b'#' {
        result.push((i - 1, j));
    }

    if j != w - 1 && grid[i][j + 1] != b'#' {
        result.push((i, j + 1));
    }

    if i != h - 1 && grid[i + 1][j] != b'#' {
        result.push((i + 1, j));
    }

    if j != 0 && grid[i][j - 1] != b'#' {
        result.push((i, j - 1));
    }

    if is_warp(grid[i][j]) {
        result.extend(
            cbw[warp_index(grid[i][j])]
                .iter()
                .filter(|&&sub| sub != (i, j)),
        )
    }

    result
}

fn min_steps(grid: Vec<Vec<u8>>) -> Option<usize> {
    let (h, w) = (grid.len(), grid[0].len());
    let cbw = crds_by_warp(&grid);
    let mut dist: HashMap<(usize, usize), usize> = HashMap::from([((0, 0), 0)]);
    let mut q: VecDeque<(usize, usize)> = VecDeque::from([(0, 0)]);

    while let Some(u) = q.pop_front() {
        for v in adjacent(&grid, &cbw, u.0, u.1) {
            let du = dist.get(&u).unwrap();

            if !dist.contains_key(&v) {
                dist.insert(v, du + 1);
                q.push_back(v);
            }
        }
    }

    dist.get(&(h - 1, w - 1)).copied()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        h: usize,
        w: usize,
        grid: [Bytes; h],
    }
    assert_eq!(grid[0].len(), w);

    let mb_result = min_steps(grid);
    if let Some(result) = mb_result {
        writeln!(writer, "{result}").unwrap();
    } else {
        writeln!(writer, "-1").unwrap();
    }
    writer.flush().unwrap();
}
