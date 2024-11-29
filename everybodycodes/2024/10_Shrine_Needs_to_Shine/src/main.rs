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

fn main() {
    let grid: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let mut s: String = String::new();
    for ro in 2..=5 {
        for co in 2..=5 {
            let xs = keep_letters(&grid[ro]);
            let ys = keep_letters(&column(&grid, co));
            s.push(*xs.intersection(&ys).next().unwrap());
        }
    }
    println!("{}", s);
}
