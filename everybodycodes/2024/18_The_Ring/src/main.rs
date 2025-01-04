use std::{
    collections::VecDeque,
    io::{self, BufRead},
};

const INF: usize = 1_000_000;

#[derive(Clone, Copy, Debug)]
struct Crd(usize, usize);

fn source_crd(grid: &[Vec<char>]) -> Crd {
    for (i, row) in grid.iter().enumerate() {
        if row[0] == '.' {
            return Crd(i, 0);
        }
    }
    panic!()
}

fn palm_crds(grid: &[Vec<char>]) -> Vec<Crd> {
    let mut result = vec![];
    for (i, row) in grid.iter().enumerate() {
        for (j, cell) in row.iter().enumerate() {
            if *cell == 'P' {
                result.push(Crd(i, j));
            }
        }
    }
    result
}

fn main() {
    let grid: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let source = source_crd(&grid);
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
            Crd(ro, co.saturating_sub(1)),
        ] {
            if distance[i][j] == INF && grid[i][j] != '#' {
                distance[i][j] = distance[ro][co] + 1;
                q.push_back(Crd(i, j));
            }
        }
    }

    let result: usize = palm_crds(&grid)
        .into_iter()
        .map(|Crd(i, j)| distance[i][j])
        .max()
        .unwrap();

    println!("{}", result);
}
