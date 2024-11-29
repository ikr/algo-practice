use std::io::{self, BufRead};

use itertools::Itertools;

fn greedy_min_stamps_for(stamps: &[i32], x: i32) -> i32 {
    let mut r = x;
    let mut result = 0;

    for stamp in stamps.iter().rev() {
        result += r / stamp;
        r %= stamp;
    }

    if r != 0 {
        i32::MAX
    } else {
        result
    }
}

fn min_stamps_for(stamps: &[i32], x: i32) -> i32 {
    stamps
        .iter()
        .powerset()
        .map(|ys| greedy_min_stamps_for(&ys.into_iter().cloned().collect::<Vec<_>>(), x))
        .min()
        .unwrap()
}

fn main() {
    let stamps = [1, 3, 5, 10, 15, 16, 20, 24, 25, 30];

    let xs: Vec<i32> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().parse().unwrap())
        .collect();

    let ys = xs
        .iter()
        .map(|&x| min_stamps_for(&stamps, x))
        .collect::<Vec<_>>();
    eprintln!("{:?}", ys);
    let result: i32 = ys.into_iter().sum();
    println!("{}", result);
}
