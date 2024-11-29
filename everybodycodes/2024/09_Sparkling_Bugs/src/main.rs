use std::io::{self, BufRead};

fn min_stamps_for(stamps: &[i32], x: i32) -> i32 {
    let mut r = x;
    let mut result = 0;

    for stamp in stamps.iter().rev() {
        result += r / stamp;
        r %= stamp;
    }

    result
}

fn main() {
    let stamps = [1, 3, 5, 10];

    let xs: Vec<i32> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().parse().unwrap())
        .collect();

    let result: i32 = xs.into_iter().map(|x| min_stamps_for(&stamps, x)).sum();
    eprintln!("{}", result);
}
