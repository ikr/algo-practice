use std::io::{self, BufRead};

const M: u64 = 16777216;

fn evolve(mut x: u64) -> u64 {
    let a = x * 64;
    x = (x ^ a) % M;
    let c = x / 32;
    x = (x ^ c) % M;
    let e = x * 2048;
    x = (x ^ e) % M;
    x
}

fn evolve_2000(mut x: u64) -> u64 {
    for _ in 0..2000 {
        x = evolve(x);
    }
    x
}

fn main() {
    let xs: Vec<u64> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().parse().unwrap())
        .collect();

    println!("{}", xs.into_iter().map(evolve_2000).sum::<u64>());
}
