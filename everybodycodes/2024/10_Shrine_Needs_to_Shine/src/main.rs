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

fn main() {
    eprintln!("{}", power("PTBVRCZHFLJWGMNS"));

    let lines: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let h = lines.len().div_ceil(9);
    let w = lines[0].len().div_ceil(9);
    eprintln!("{} x {} grids", h, w);

    let mut result: usize = 0;
    for i in 0..h {
        for j in 0..w {
            let mut grid: Vec<Vec<char>> = vec![];

            for line in lines.iter().skip(i * 9).take(8) {
                grid.push(line[j * 9..j * 9 + 8].to_vec());
            }

            result += power(&center_piece(&grid));
        }
    }
    println!("{}", result);
}
