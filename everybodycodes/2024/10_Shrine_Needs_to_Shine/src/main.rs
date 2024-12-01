use std::{
    collections::HashSet,
    io::{self, BufRead},
};

use itertools::Itertools;

fn keep_letters(xs: &[u8]) -> HashSet<u8> {
    xs.iter()
        .cloned()
        .filter(|x| x.is_ascii_uppercase())
        .collect()
}

fn grid_at(lines: &[Vec<u8>], i: usize, j: usize) -> Grid {
    let mut grid: Vec<Vec<u8>> = vec![];

    for line in lines.iter().skip(i * 6).take(8) {
        grid.push(line[j * 6..j * 6 + 8].to_vec());
    }
    Grid { i, j, grid }
}

fn power(s: &[u8]) -> usize {
    s.iter()
        .enumerate()
        .map(|(i, b)| (i + 1) * ((b - b'A' + 1) as usize))
        .sum()
}

#[derive(Clone)]
struct Grid {
    i: usize,
    j: usize,
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

        Grid {
            i: self.i,
            j: self.j,
            grid,
        }
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

    fn reinsert_tile(&self, lines: &mut [Vec<u8>]) {
        for (ro, row) in self.grid.iter().enumerate() {
            for (co, cell) in row.iter().enumerate() {
                lines[self.i * 6 + ro][self.j * 6 + co] = *cell;
            }
        }
    }

    fn locations_of_unknowns(&self) -> Vec<(usize, usize)> {
        let mut result = vec![];
        for (ro, row) in self.grid.iter().enumerate() {
            for (co, cell) in row.iter().enumerate() {
                if *cell == b'?' {
                    result.push((ro, co));
                }
            }
        }
        result
    }

    fn complete_variants(&self) -> Vec<Grid> {
        let g0 = self.fill_all_possible();
        let taken: Vec<u8> = g0
            .center_piece()
            .into_iter()
            .filter(|x| x.is_ascii_uppercase())
            .collect();
        let avs: Vec<u8> = (b'A'..=b'Z').filter(|x| !taken.contains(x)).collect();

        let uks = self.locations_of_unknowns();
        assert!(!uks.is_empty());

        (0..uks.len())
            .map(|_| avs.clone())
            .multi_cartesian_product()
            .filter(|xs| xs.iter().collect::<HashSet<_>>().len() == uks.len())
            .map(|substitutions| {
                let mut g = self.clone();
                for (x, (ro, co)) in substitutions.into_iter().zip(uks.iter()) {
                    g.grid[*ro][*co] = x;
                }
                g.fill_all_possible()
            })
            .filter(|g| g.is_complete())
            .collect()
    }

    fn eprint(&self) {
        for row in self.grid.iter() {
            eprintln!("{}", String::from_utf8(row.to_vec()).unwrap());
        }
    }
}

fn replace_first_unambiguous(&mut lines: Vec<Vec<u8>>) -> bool {
    let h = lines.len() / 6;
    let w = lines[0].len() / 6;

    for i in 0..h {
        for j in 0..w {
            let g = grid_at(&lines, i, j);
            if g.is_complete() {
                continue;
            }

            let gg = g.fill_all_possible();

            if gg.is_complete() {
                gg.reinsert_tile(&mut lines);
                return true;
            } else if !g.locations_of_unknowns().is_empty() {
                let vs = g.complete_variants();
                if vs.len() == 1 {
                    let v = vs.first().unwrap();
                    v.reinsert_tile(&mut lines);
                    return true;
                }
            };
        }
    }

    false
}

fn main() {
    let initial_lines: Vec<Vec<u8>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().bytes().collect())
        .collect();

    let h = initial_lines.len() / 6;
    let w = initial_lines[0].len() / 6;

    for i in 0..h {
        for j in 0..w {
            let g = grid_at(&initial_lines, i, j);
            let gg = g.fill_all_possible();

            let num_variants: usize = if gg.is_complete() {
                1
            } else if g.locations_of_unknowns().is_empty() {
                0
            } else {
                g.complete_variants().len()
            };

            eprint!("{} ", num_variants);
        }
        eprintln!();
    }
}
