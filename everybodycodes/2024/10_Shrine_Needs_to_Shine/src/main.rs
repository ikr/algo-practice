use std::{
    collections::HashSet,
    io::{self, BufRead},
};

fn column(grid: &[Vec<char>], co: usize) -> Vec<char> {
    grid.iter().fold(vec![], |mut acc, row| {
        acc.push(row[co]);
        acc
    })
}

fn keep_letters(xs: &[char]) -> HashSet<char> {
    xs.iter()
        .cloned()
        .filter(|x| x.is_ascii_uppercase())
        .collect()
}

fn center_piece(grid: &[Vec<char>]) -> String {
    let mut s: String = String::new();
    for ro in 2..=5 {
        for co in 2..=5 {
            let xs = keep_letters(&grid[ro]);
            let ys = keep_letters(&column(grid, co));
            s.push(*xs.intersection(&ys).next().unwrap());
        }
    }
    s
}

fn power(s: &str) -> usize {
    s.bytes()
        .enumerate()
        .map(|(i, b)| (i + 1) * ((b - b'A' + 1) as usize))
        .sum()
}

fn grid_at(lines: &[Vec<char>], i: usize, j: usize) -> Vec<Vec<char>> {
    let mut grid: Vec<Vec<char>> = vec![];

    for line in lines.iter().skip(i * 6).take(8) {
        grid.push(line[j * 6..j * 6 + 8].to_vec());
    }
    grid
}

fn eprint_grid(grid: &[Vec<char>]) {
    for row in grid {
        eprintln!("{}", row.iter().collect::<String>());
    }
}

fn reinsert_tile(lines: &mut [Vec<char>], i: usize, j: usize, grid: &[Vec<char>]) {
    for (ro, row) in grid.iter().enumerate() {
        for (co, cell) in row.iter().enumerate() {
            lines[i * 6 + ro][j * 6 + co] = *cell;
        }
    }
}

struct Grid {
    grid: Vec<Vec<char>>,
}

impl Grid {
    fn fill_all_possible(&mut self) {
        for ro in 2..=5 {
            for co in 2..=5 {
                let xs = keep_letters(&self.grid[ro]);
                let ys = keep_letters(&column(&self.grid, co));
                let zs = xs.intersection(&ys).cloned().collect::<Vec<char>>();
                if let Some(&c) = zs.first() {
                    if zs.len() == 1 {
                        self.grid[ro][co] = c;
                    }
                }
            }
        }
    }
}

fn main() {
    let mut lines: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let h = lines.len() / 6;
    let w = lines[0].len() / 6;

    for i in 0..h {
        for j in 0..w {
            let mut g = Grid {
                grid: grid_at(&lines, i, j),
            };
            g.fill_all_possible();
            reinsert_tile(&mut lines, i, j, &g.grid);
        }
    }

    for i in 0..h {
        for j in 0..w {
            eprint_grid(&grid_at(&lines, i, j));
            eprintln!();
        }
    }
}
