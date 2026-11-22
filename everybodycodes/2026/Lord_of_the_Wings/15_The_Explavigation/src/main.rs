use std::io::{BufRead, stdin};

fn main() {
    let grid: Vec<Vec<char>> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    eprintln!("{grid:?}");
}
