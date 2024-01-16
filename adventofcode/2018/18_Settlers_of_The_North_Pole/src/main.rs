use std::io::{self, BufRead};

fn safe_at(grid: &[Vec<char>], ro: i32, co: i32) -> char {
    let h = grid.len() as i32;
    assert!(!grid.is_empty());
    let w = grid[0].len() as i32;
    if 0 <= ro && ro < h && 0 <= co && co < w {
        grid[ro as usize][co as usize]
    } else {
        ' '
    }
}

fn neighs_count(grid: &[Vec<char>], kind: char, ro: i32, co: i32) -> i32 {
    let mut count = 0;
    for dr in -1..=1 {
        for dc in -1..=1 {
            if dr == 0 && dc == 0 {
                continue;
            }
            if safe_at(grid, ro + dr, co + dc) == kind {
                count += 1;
            }
        }
    }
    count
}

fn evolve(grid: &[Vec<char>]) -> Vec<Vec<char>> {
    let h = grid.len();
    assert!(!grid.is_empty());
    let w = grid[0].len();
    let mut result = vec![vec![' '; w]; h];

    for ro in 0..h {
        for co in 0..w {
            let u = grid[ro][co];
            result[ro][co] = u;

            if u == '.' {
                if neighs_count(grid, '|', ro as i32, co as i32) >= 3 {
                    result[ro][co] = '|';
                }
            } else if u == '|' {
                if neighs_count(grid, '#', ro as i32, co as i32) >= 3 {
                    result[ro][co] = '#';
                }
            } else {
                assert!(u == '#');
                if neighs_count(grid, '#', ro as i32, co as i32) >= 1
                    && neighs_count(grid, '|', ro as i32, co as i32) >= 1
                {
                    result[ro][co] = '#';
                } else {
                    result[ro][co] = '.';
                }
            }
        }
    }

    result
}

fn resource_value(grid: &[Vec<char>]) -> i32 {
    let mut trees = 0;
    let mut lumberyards = 0;
    for row in grid {
        for u in row {
            if *u == '|' {
                trees += 1;
            } else if *u == '#' {
                lumberyards += 1;
            }
        }
    }
    trees * lumberyards
}

fn main() {
    let mut grid: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let pre = 6_000;
    let mut xs: Vec<i32> = Vec::new();

    for _ in 0..pre {
        grid = evolve(&grid);
        xs.push(resource_value(&grid));
    }

    let mut pat: Vec<i32> = Vec::new();
    loop {
        if pat.is_empty() {
            pat.push(xs.pop().unwrap());
        } else {
            if pat.len() > 1 && pat[0] == *xs.last().unwrap() {
                break;
            }
            pat.push(xs.pop().unwrap());
        }
    }
    pat.reverse();

    let mut t: i32 = 1_000_000_000 - 1;
    t -= pre - pat.len() as i32;
    println!("{}", pat[(t % pat.len() as i32) as usize]);
}
