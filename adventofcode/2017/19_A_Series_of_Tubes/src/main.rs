use std::io::{self, BufRead};

fn main() {
    let grid: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|x| x.unwrap().chars().collect())
        .collect();

    eprintln!("{:?}", grid);
}
