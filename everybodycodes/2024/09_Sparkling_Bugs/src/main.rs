use std::io::{self, BufRead};

use memoise::memoise;

const INF: u32 = 1_000_000;

#[memoise(stamps.len(), x)]
fn min_stamps_for(stamps: &[u16], x: u16) -> u32 {
    if x == 0 {
        0
    } else if let Some(y) = stamps.last() {
        let fewer_stamps: Vec<u16> = stamps[0..stamps.len() - 1].to_vec();
        if y > &x {
            min_stamps_for(&fewer_stamps, x)
        } else {
            min_stamps_for(&fewer_stamps, x).min(1 + min_stamps_for(stamps, x - y))
        }
    } else {
        INF
    }
}

fn main() {
    let stamps: Vec<u16> = vec![1, 3, 5, 10, 15, 16, 20, 24, 25, 30];

    let xs: Vec<u16> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().parse().unwrap())
        .collect();

    let ys = xs
        .into_iter()
        .map(|x| min_stamps_for(&stamps, x))
        .collect::<Vec<_>>();
    eprintln!("{:?}", ys);
    let result: u32 = ys.into_iter().sum();
    println!("{}", result);
}
