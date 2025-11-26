use itertools::Itertools;
use std::io::{BufRead, stdin};

const R: usize = 10;

fn crd_of_x(grid: &[Vec<u16>], x: u16) -> (usize, usize) {
    let h = grid.len();
    let w = grid[0].len();

    (0..h)
        .cartesian_product(0..w)
        .find(|&(i, j)| grid[i][j] == x)
        .unwrap()
}

fn main() {
    let grid: Vec<Vec<u16>> = stdin()
        .lock()
        .lines()
        .map(|line| {
            line.unwrap()
                .bytes()
                .map(|x| if x == b'@' { 0 } else { (x - b'0') as u16 })
                .collect()
        })
        .collect();

    let h = grid.len();
    let w = grid[0].len();
    eprintln!("{h} x {w}");
    let (zi, zj) = crd_of_x(&grid, 0);

    let mut radius: Vec<Vec<usize>> = vec![vec![0; w]; h];

    for i in 0..h {
        for j in 0..w {
            radius[i][j] = (zi.abs_diff(i).pow(2) + zj.abs_diff(j).pow(2)).isqrt();
        }
    }

    eprintln!("{:?}", radius);
}
