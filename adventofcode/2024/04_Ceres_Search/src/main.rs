use std::{
    collections::HashSet,
    io::{self, BufRead},
};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i32, i32);

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

fn read_path(grid: &[Vec<char>], start: Crd, direction: Crd, length: usize) -> Vec<char> {
    let mut path = Vec::new();
    let mut cur = start;
    loop {
        path.push(grid[cur.0 as usize][cur.1 as usize]);
        if path.len() == length {
            break;
        }
        cur = cur + direction;
        if cur.0 < 0 || cur.0 >= grid.len() as i32 || cur.1 < 0 || cur.1 >= grid[0].len() as i32 {
            break;
        }
    }
    path
}

fn main() {
    let grid: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let mut result = 0;
    let h = grid.len() as i32;
    let w = grid[0].len() as i32;

    for ro in 0..h {
        for co in 0..w {
            for dr in -1..=1 {
                for dc in -1..=1 {
                    if dr == 0 && dc == 0 {
                        continue;
                    }
                    let direction = Crd(dr, dc);
                    let path = read_path(&grid, Crd(ro, co), direction, 4);
                    if path == vec!['X', 'M', 'A', 'S'] {
                        result += 1;
                    }
                }
            }
        }
    }
    println!("{}", result);
}
