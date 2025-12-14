use proconio::input;
use proconio::marker::Bytes;
use std::{
    collections::{HashMap, HashSet, VecDeque},
    io::{BufWriter, Write, stdout},
};

fn is_warp(x: u8) -> bool {
    b'a' <= x && x <= b'z'
}

fn warp_index(x: u8) -> Option<usize> {
    is_warp(x).then(|| (x - b'a') as usize)
}

fn crds_by_warp(grid: &[Vec<u8>]) -> Vec<Vec<(usize, usize)>> {
    let mut result = vec![vec![]; 26];

    for (i, row) in grid.iter().enumerate() {
        for (j, cell) in row.iter().enumerate() {
            if let Some(wi) = warp_index(*cell) {
                result[wi].push((i, j));
            }
        }
    }

    result
}

fn adjacent_by_warp(grid: &[Vec<u8>]) -> Vec<Vec<(usize, usize)>> {
    let (h, w) = (grid.len(), grid[0].len());
    let mut result: Vec<HashSet<(usize, usize)>> = vec![HashSet::new(); 26];

    for i in 0..h {
        for j in 0..w {
            if let Some(wi) = warp_index(grid[i][j]) {
                result[wi].extend(
                    adjacent(grid, i, j)
                        .into_iter()
                        .filter(|&(ii, jj)| grid[ii][jj] != grid[i][j]),
                );
            }
        }
    }

    result
        .into_iter()
        .map(|hs| hs.into_iter().collect())
        .collect()
}

fn adjacent(grid: &[Vec<u8>], i: usize, j: usize) -> Vec<(usize, usize)> {
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

    result
}

fn min_steps(grid: Vec<Vec<u8>>) -> Option<usize> {
    let (h, w) = (grid.len(), grid[0].len());

    if let Some(wi_start) = warp_index(grid[0][0])
        && let Some(wi_finish) = warp_index(grid[h - 1][w - 1])
        && wi_start == wi_finish
    {
        return Some(1);
    }

    let cbw = crds_by_warp(&grid);
    let abw = adjacent_by_warp(&grid);
    let mut dist: HashMap<(usize, usize), usize> = HashMap::from([((0, 0), 0)]);
    let mut q: VecDeque<(usize, usize)> = VecDeque::from([(0, 0)]);

    while let Some(u) = q.pop_front() {
        let du: usize = *dist.get(&u).unwrap();

        if let Some(wi) = warp_index(grid[u.0][u.1]) {
            if let Some(wi_finish) = warp_index(grid[h - 1][w - 1])
                && wi_finish == wi
            {
                return Some(du + 1);
            }

            for &v in &abw[wi] {
                if v == (h - 1, w - 1) {
                    let incr = if adjacent(&grid, v.0, v.1).contains(&u) {
                        1
                    } else {
                        2
                    };
                    return Some(du + incr);
                }

                if !dist.contains_key(&v) {
                    let incr = if adjacent(&grid, v.0, v.1).contains(&u) {
                        1
                    } else {
                        2
                    };
                    dist.extend(cbw[wi].iter().map(|&(i, j)| {
                        let incr = if adjacent(&grid, i, j).contains(&u) {
                            1
                        } else {
                            2
                        };
                        ((i, j), du + incr)
                    }));
                    dist.insert(v, du + incr);
                    q.push_back(v);
                }
            }
        } else {
            for v in adjacent(&grid, u.0, u.1) {
                if !dist.contains_key(&v) {
                    if v == (h - 1, w - 1) {
                        return Some(du + 1);
                    }
                    dist.insert(v, du + 1);
                    q.push_back(v);
                }
            }
        }
    }

    None
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
