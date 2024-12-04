use std::io::{self, BufRead};

#[derive(Clone, Copy)]
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
        if cur.0 < 0 || cur.0 >= grid.len() as i32 || cur.1 < 0 || cur.1 >= grid[0].len() as i32 {
            break;
        }
        path.push(grid[cur.0 as usize][cur.1 as usize]);
        if path.len() == length {
            break;
        }
        cur = cur + direction;
    }
    path
}

fn is_mas(xs: &[char]) -> bool {
    xs == ['M', 'A', 'S'] || xs == ['S', 'A', 'M']
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
            let one = read_path(&grid, Crd(ro, co), Crd(1, 1), 3);
            let two = read_path(&grid, Crd(ro + 2, co), Crd(-1, 1), 3);

            if is_mas(&one) && is_mas(&two) {
                result += 1;
            }
        }
    }
    println!("{}", result);
}
