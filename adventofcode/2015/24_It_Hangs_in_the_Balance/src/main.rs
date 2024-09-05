use std::io::{self, BufRead};

fn main() {
    let xs: Vec<i32> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().parse().unwrap())
        .collect();

    eprintln!("{:?}, {} elements", xs, xs.len());
}
