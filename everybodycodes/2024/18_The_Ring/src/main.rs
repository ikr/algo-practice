use std::{
    collections::VecDeque,
    io::{self, BufRead},
};

const INF: usize = 1_000_000;

#[derive(Clone, Copy, Debug)]
struct Crd(usize, usize);

fn crds_of(grid: &[Vec<char>], c: char) -> Vec<Crd> {
    let mut result = vec![];
    for (i, row) in grid.iter().enumerate() {
        for (j, cell) in row.iter().enumerate() {
            if *cell == c {
                result.push(Crd(i, j));
            }
        }
    }
    result
}

fn distances_for_given_source(grid: &[Vec<char>], source: Crd) -> Vec<Vec<usize>> {
    let h = grid.len();
    let w = grid[0].len();

    let mut distance: Vec<Vec<usize>> = vec![vec![INF; w]; h];
    distance[source.0][source.1] = 0;

    let mut q: VecDeque<Crd> = VecDeque::new();
    q.push_back(source);

    while let Some(u) = q.pop_front() {
        let Crd(ro, co) = u;
        for Crd(i, j) in [
            Crd(ro - 1, co),
            Crd(ro, co + 1),
            Crd(ro + 1, co),
            Crd(ro, co - 1),
        ] {
            if distance[i][j] == INF && grid[i][j] != '#' {
                distance[i][j] = distance[ro][co] + 1;
                q.push_back(Crd(i, j));
            }
        }
    }

    distance
}

fn main() {
    let grid: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let ps = crds_of(&grid, 'P');
    let result = crds_of(&grid, '.')
        .into_iter()
        .map(|source| -> usize {
            let dist = distances_for_given_source(&grid, source);
            ps.iter().map(|p| dist[p.0][p.1]).sum()
        })
        .min()
        .unwrap();
    println!("{}", result);
}
