use itertools::Itertools;
use std::io::{BufRead, stdin};

fn crd_of_x(grid: &[Vec<u64>], x: u64) -> (usize, usize) {
    let h = grid.len();
    let w = grid[0].len();

    (0..h)
        .cartesian_product(0..w)
        .find(|&(i, j)| grid[i][j] == x)
        .unwrap()
}

fn main() {
    let grid: Vec<Vec<u64>> = stdin()
        .lock()
        .lines()
        .map(|line| {
            line.unwrap()
                .bytes()
                .map(|x| if x == b'@' { 0 } else { (x - b'0') as u64 })
                .collect()
        })
        .collect();

    let h = grid.len();
    let w = grid[0].len();
    eprintln!("{h} x {w}");
    let (zi, zj) = crd_of_x(&grid, 0);

    let mut damage_by_radius: Vec<u64> = vec![0; (h.pow(2) + w.pow(2)).isqrt() + 2];
    let mut radius: Vec<Vec<usize>> = vec![vec![0; w]; h];

    for (i, row) in grid.into_iter().enumerate() {
        for (j, cell) in row.into_iter().enumerate() {
            let r2 = zi.abs_diff(i).pow(2) + zj.abs_diff(j).pow(2);

            let r = if r2.isqrt().pow(2) == r2 {
                r2.isqrt()
            } else {
                r2.isqrt() + 1
            };

            radius[i][j] = r;
            damage_by_radius[r] += cell;
        }
    }

    eprintln!("{:?}", radius);
    eprintln!("{:?}", damage_by_radius);

    let (r, damage) = damage_by_radius
        .into_iter()
        .enumerate()
        .max_by_key(|&(_, d)| d)
        .unwrap();

    println!("{}", (r as u64) * damage);
}
