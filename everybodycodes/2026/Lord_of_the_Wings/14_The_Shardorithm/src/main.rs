use std::{
    collections::HashSet,
    io::{BufRead, stdin},
};

use ac_library::Dsu;

fn main() {
    let grid: Vec<Vec<char>> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let height = grid.len();
    let width = grid[0].len();
    let mut dsu = Dsu::new(height * width);

    for (i, row) in grid.iter().enumerate() {
        for (j, &cell) in row.iter().enumerate() {
            let u = i * width + j;

            if i != 0 && grid[i - 1][j] == cell {
                dsu.merge(u, (i - 1) * width + j);
            }

            if j != width - 1 && grid[i][j + 1] == cell {
                dsu.merge(u, i * width + j + 1);
            }

            if i != height - 1 && grid[i + 1][j] == cell {
                dsu.merge(u, (i + 1) * width + j);
            }

            if j != 0 && grid[i][j - 1] == cell {
                dsu.merge(u, i * width + j - 1);
            }
        }
    }

    let mut result: usize = 0;
    let mut vert_covered: HashSet<(usize, usize)> = HashSet::new();
    let mut horz_covered: HashSet<(usize, usize)> = HashSet::new();

    for group in dsu.groups() {
        eprintln!("{group:?}");
        let mut sub: usize = 0;

        for u in group {
            let (i, j) = (u / width, u % width);
            let cell = grid[i][j];

            if i == 0 {
                sub += 1;
            } else if grid[i - 1][j] != cell && !horz_covered.contains(&(i, j)) {
                horz_covered.insert((i, j));
                sub += 1;
            }

            if j == width - 1 {
                sub += 1;
            } else if grid[i][j + 1] != cell && !vert_covered.contains(&(i, j + 1)) {
                vert_covered.insert((i, j + 1));
                sub += 1;
            }

            if i == height - 1 {
                sub += 1
            } else if grid[i + 1][j] != cell && !horz_covered.contains(&(i + 1, j)) {
                horz_covered.insert((i + 1, j));
                sub += 1;
            }

            if j == 0 {
                sub += 1;
            } else if grid[i][j - 1] != cell && vert_covered.contains(&(i, j)) {
                vert_covered.insert((i, j));
                sub += 1;
            }

            eprint!("({i}, {j}):{sub} ");
        }

        eprintln!();
        result += sub;
    }

    println!("{result}");
}
