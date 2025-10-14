use std::collections::{HashSet, VecDeque};

use ac_library::Dsu;
use proconio::input;
use proconio::marker::Bytes;
use proconio_derive::fastout;

fn largest_connected_component(h: usize, w: usize, coords: HashSet<(usize, usize)>) -> usize {
    let code = |i: usize, j: usize| -> usize { i * w + j };
    let mut dsu = Dsu::new(h * w);

    let adjacent = |i0: usize, j0: usize| -> Vec<(usize, usize)> {
        let mut result = vec![];

        if i0 != 0 && coords.contains(&(i0 - 1, j0)) {
            result.push((i0 - 1, j0));
        }

        if j0 != w - 1 && coords.contains(&(i0, j0 + 1)) {
            result.push((i0, j0 + 1));
        }

        if i0 != h - 1 && coords.contains(&(i0 + 1, j0)) {
            result.push((i0 + 1, j0));
        }

        if j0 != 0 && coords.contains(&(i0, j0 - 1)) {
            result.push((i0, j0 - 1));
        }

        result
    };

    for (i0, j0) in &coords {
        for (i, j) in adjacent(*i0, *j0) {
            dsu.merge(code(*i0, *j0), code(i, j));
        }
    }

    dsu.groups().into_iter().map(|g| g.len()).max().unwrap()
}

fn largest_connected_safe_area(grid: Vec<Vec<u8>>, spaces: usize) -> usize {
    let h = grid.len();
    let w = grid[0].len();
    let mut dist: Vec<Vec<usize>> = vec![vec![usize::MAX; w]; h];
    let mut q: VecDeque<(usize, usize)> = VecDeque::new();

    for (i, row) in grid.iter().enumerate() {
        for (j, &cell) in row.iter().enumerate() {
            if cell == b'#' {
                dist[i][j] = 0;
                q.push_back((i, j));
            }
        }
    }

    let adjacent = |i0: usize, j0: usize| -> Vec<(usize, usize)> {
        let mut result = vec![];

        if i0 != 0 && grid[i0 - 1][j0] != b'#' {
            result.push((i0 - 1, j0));
        }

        if j0 != w - 1 && grid[i0][j0 + 1] != b'#' {
            result.push((i0, j0 + 1));
        }

        if i0 != h - 1 && grid[i0 + 1][j0] != b'#' {
            result.push((i0 + 1, j0));
        }

        if j0 != 0 && grid[i0][j0 - 1] != b'#' {
            result.push((i0, j0 - 1));
        }

        result
    };

    while let Some((i0, j0)) = q.pop_front() {
        assert_ne!(dist[i0][j0], usize::MAX);

        for (i, j) in adjacent(i0, j0) {
            if dist[i][j] == usize::MAX {
                dist[i][j] = dist[i0][j0] + 1;
                q.push_back((i, j));
            }
        }
    }

    let some_safe: bool = dist.iter().any(|ds| ds.iter().any(|d| *d > spaces));

    if some_safe {
        let mut safe: HashSet<(usize, usize)> = HashSet::new();
        for (i, ds) in dist.into_iter().enumerate() {
            for (j, d) in ds.into_iter().enumerate() {
                if d > spaces {
                    safe.insert((i, j));
                }
            }
        }
        largest_connected_component(h, w, safe)
    } else {
        0
    }
}

#[fastout]
fn main() {
    input! {
        cases_num: u16,
    }

    for t in 1..=cases_num {
        input! {
            n: usize,
            m: usize,
            spaces: usize,
            mut grid: [Bytes; n],
        }

        assert_eq!(grid[0].len(), m);
        assert_eq!(grid[n - 1].len(), m);

        for row in &mut grid {
            row.insert(0, b'#');
            row.push(b'#');
        }

        grid.insert(0, vec![b'#'; m + 2]);
        grid.push(vec![b'#'; m + 2]);

        let result = largest_connected_safe_area(grid, spaces);
        println!("Case #{t}: {result}");
    }
}
