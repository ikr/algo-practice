use ac_library::Dsu;
use itertools::{
    Itertools,
    MinMaxResult::{MinMax, NoElements, OneElement},
};
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

fn top_bottom(ps: &[(usize, usize)]) -> (usize, usize) {
    match ps.iter().map(|(ro, _)| *ro).minmax() {
        MinMax(a, b) => (a, b),
        OneElement(a) => (a, a),
        NoElements => panic!(),
    }
}

fn left_right(ps: &[(usize, usize)]) -> (usize, usize) {
    match ps.iter().map(|(_, co)| *co).minmax() {
        MinMax(a, b) => (a, b),
        OneElement(a) => (a, a),
        NoElements => panic!(),
    }
}

fn clusters(ps: Vec<(usize, usize)>) -> Vec<Vec<(usize, usize)>> {
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

fn l_cluster_ray_coverage_size(cluster: Vec<(usize, usize)>) -> usize {
    let (top, bottom) = top_bottom(&cluster);
    let (left, right) = left_right(&cluster);
    let corners = [(top, left), (top, right), (bottom, right), (bottom, left)];

    if let Some(i_empty_point) = corners.iter().find(|p| !cluster.contains(p)) {
        todo!()
    } else {
        (bottom - top).min(right - left) + 1
    }
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

    let cs = clusters(magma);
    let result: usize = cs.into_iter().map(l_cluster_ray_coverage_size).sum();
    println!("{result}");
}
