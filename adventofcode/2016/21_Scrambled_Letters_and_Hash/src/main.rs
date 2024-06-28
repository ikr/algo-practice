use std::io::{self, BufRead};

enum Op {
    SwpPos(usize, usize),
    SwpLtr(u8, u8),
    RotL(usize),
    RotR(usize),
    Rbop(u8),
    Rev(usize, usize),
    Mov(usize, usize),
}

fn main() {
    let grid: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();
}
