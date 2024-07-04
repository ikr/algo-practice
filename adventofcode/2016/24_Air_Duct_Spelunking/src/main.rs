use std::io::{self, BufRead};

fn main() {
    let grid: Vec<Vec<u8>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().into_bytes())
        .collect();

    eprintln!("{:?}", grid);
}
