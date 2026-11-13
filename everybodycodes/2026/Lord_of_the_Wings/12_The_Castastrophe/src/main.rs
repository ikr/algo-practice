use ac_library::Dsu;
use std::io::{BufRead, stdin};

fn adjacent(ij: (usize, usize)) -> Vec<(usize, usize)> {
    let (i, j) = ij;
    let mut result = vec![(i + 1, j), (i, j + 1)];

    if i != 0 {
        result.push((i - 1, j));
    }

    if j != 0 {
        result.push((i, j - 1));
    }

    result
}

fn left_top(ps: &[(usize, usize)]) -> (usize, usize) {
    *ps.iter().min().unwrap()
}

fn right_bottom(ps: &[(usize, usize)]) -> (usize, usize) {
    *ps.iter().max().unwrap()
}

fn clusters(ps: &[(usize, usize)]) -> Vec<Vec<(usize, usize)>> {
    let mut dsu: Dsu = ps
        .iter()
        .enumerate()
        .fold(Dsu::new(ps.len()), |mut agg, (u, &roco)| {
            for pq in adjacent(roco) {
                if let Some(v) = ps.iter().position(|&xy| xy == pq) {
                    agg.merge(u, v);
                }
            }
            agg
        });

    dsu.groups()
        .into_iter()
        .map(|group| group.into_iter().map(|i| ps[i]).collect())
        .collect()
}

fn main() {
    let grid: Vec<Vec<u8>> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().bytes().collect())
        .collect();

    let magma: Vec<(usize, usize)> = grid
        .into_iter()
        .enumerate()
        .flat_map(move |(i, row)| {
            row.into_iter()
                .enumerate()
                .filter_map(move |(j, x)| (x == b'#').then_some((i, j)))
        })
        .collect();

    let cs = clusters(&magma);

    let result: usize = cs
        .into_iter()
        .map(|ctr| {
            let (left, top) = left_top(&ctr);
            let (right, bottom) = right_bottom(&ctr);
            (right - left).min(bottom - top) + 1
        })
        .sum();

    println!("{result}");
}
