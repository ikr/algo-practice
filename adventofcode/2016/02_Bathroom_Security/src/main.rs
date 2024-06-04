use std::io::{self, BufRead};

fn main() {
    let instruction_lines: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect::<Vec<char>>())
        .collect();
    eprintln!("{:?}", instruction_lines);
}
