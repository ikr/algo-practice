use std::{
    collections::HashSet,
    io::{self, BufRead},
};

fn keep_letters(xs: &[u8]) -> HashSet<u8> {
    xs.iter()
        .cloned()
        .filter(|x| x.is_ascii_uppercase())
        .collect()
}

fn grid_at(lines: &[Vec<u8>], i: usize, j: usize) -> Vec<Vec<u8>> {
    let mut grid: Vec<Vec<u8>> = vec![];

    for line in lines.iter().skip(i * 6).take(8) {
        grid.push(line[j * 6..j * 6 + 8].to_vec());
    }
    grid
}

fn eprint_grid(grid: &[Vec<u8>]) {
    for row in grid {
        eprintln!("{}", String::from_utf8(row.to_vec()).unwrap());
    }
}

fn reinsert_tile(lines: &mut [Vec<u8>], i: usize, j: usize, grid: &[Vec<u8>]) {
    for (ro, row) in grid.iter().enumerate() {
        for (co, cell) in row.iter().enumerate() {
            lines[i * 6 + ro][j * 6 + co] = *cell;
        }
    }
}

fn power(s: &[u8]) -> usize {
    s.iter()
        .enumerate()
        .map(|(i, b)| (i + 1) * ((b - b'A' + 1) as usize))
        .sum()
}

struct Grid {
    grid: Vec<Vec<u8>>,
}

impl Grid {
    fn column(&self, co: usize) -> Vec<u8> {
        self.grid.iter().fold(vec![], |mut acc, row| {
            acc.push(row[co]);
            acc
        })
    }

    fn fill_all_possible(&self) -> Grid {
        let mut grid = self.grid.clone();

        for (ro, row) in self.grid.iter().enumerate().skip(2).take(4) {
            for co in 2..=5 {
                let xs = keep_letters(row);
                let ys = keep_letters(&self.column(co));
                let zs = xs.intersection(&ys).cloned().collect::<Vec<u8>>();
                if let Some(&c) = zs.first() {
                    if zs.len() == 1 {
                        grid[ro][co] = c;
                    }
                }
            }
        }

        Grid { grid }
    }

    fn is_complete(&self) -> bool {
        let xs: HashSet<u8> = self
            .center_piece()
            .into_iter()
            .filter(|x| x.is_ascii_uppercase())
            .collect();
        xs.len() == 16
    }

    fn center_piece(&self) -> Vec<u8> {
        let mut s = vec![];
        for ro in 2..=5 {
            for co in 2..=5 {
                s.push(self.grid[ro][co]);
            }
        }
        s
    }
}

fn main() {
    let mut lines: Vec<Vec<u8>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().bytes().collect())
        .collect();

    let h = lines.len() / 6;
    let w = lines[0].len() / 6;

    for i in 0..h {
        for j in 0..w {
            let g = Grid {
                grid: grid_at(&lines, i, j),
            };
            let gg = g.fill_all_possible();
            reinsert_tile(&mut lines, i, j, &gg.grid);
        }
    }

    for i in 0..h {
        for j in 0..w {
            eprint_grid(&grid_at(&lines, i, j));
            eprintln!();
        }
    }
}
