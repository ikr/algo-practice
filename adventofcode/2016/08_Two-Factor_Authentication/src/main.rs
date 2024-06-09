use std::io::{self, BufRead};

const H: usize = 3;
const W: usize = 7;

fn main() {
    let grid: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();
}
