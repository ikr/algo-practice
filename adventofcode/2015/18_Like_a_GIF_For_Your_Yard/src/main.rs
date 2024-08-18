use itertools::Itertools;
use std::io::{self, BufRead};

// fn print_to_stderr(grid: &[Vec<bool>]) {
//     for row in grid {
//         eprintln!(
//             "{}",
//             row.iter()
//                 .map(|x| if *x { '#' } else { '.' })
//                 .collect::<String>()
//         );
//     }
// }

fn neighs_count(grid: &[Vec<bool>], ro: usize, co: usize) -> u8 {
    let h = grid.len() as i8;
    assert!(h > 0);
    let w = grid[0].len() as i8;

    let r = ro as i8;
    let c = co as i8;
    assert!(r < h);
    assert!(c < w);

    let rocos = (-1..=1)
        .cartesian_product(-1..=1)
        .filter(|(di, dj)| !(*di == 0 && *dj == 0))
        .map(|(di, dj)| (r + di, c + dj))
        .filter(|(i, j)| 0 <= *i && *i < h && 0 <= *j && *j < w)
        .map(|(i, j)| (i as usize, j as usize));

    rocos.fold(0, |acc, (i, j)| if grid[i][j] { acc + 1 } else { acc })
}

fn evolve(grid: &[Vec<bool>]) -> Vec<Vec<bool>> {
    let h = grid.len();
    assert!(h > 0);
    let w = grid[0].len();

    let mut result = vec![vec![false; w]; h];
    for r in 0..h {
        for c in 0..w {
            let ns = neighs_count(grid, r, c);

            if grid[r][c] {
                result[r][c] = ns == 2 || ns == 3;
            } else {
                result[r][c] = ns == 3;
            }
        }
    }
    result
}

fn trues_count(grid: &[Vec<bool>]) -> usize {
    grid.iter()
        .fold(0, |acc, row| acc + row.iter().filter(|x| **x).count())
}

fn main() {
    let grid: Vec<Vec<bool>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().bytes().map(|b| b == b'#').collect())
        .collect();

    let mut cur = grid.clone();
    for _ in 0..100 {
        cur = evolve(&cur);
    }
    println!("{}", trues_count(&cur));
}
