use std::io::{self, BufRead};

use memoise::memoise;

const INF: u32 = 1_000_000;
const STAMPS: [u8; 18] = [
    1, 3, 5, 10, 15, 16, 20, 24, 25, 30, 37, 38, 49, 50, 74, 75, 100, 101,
];

#[memoise(n <= 20, x <= 120_000)]
fn min_stamps_for(n: u8, x: u32) -> u32 {
    if x == 0 {
        0
    } else if n > 0 {
        let y = STAMPS[(n as usize) - 1];
        if y as u32 > x {
            min_stamps_for(n - 1, x)
        } else {
            min_stamps_for(n - 1, x).min(1 + min_stamps_for(n, x - y as u32))
        }
    } else {
        INF
    }
}

fn optimal_split(x: u32) -> (u32, u32) {
    let mut lo = INF;
    let mut result: (u32, u32) = (INF, INF);

    for y in x / 2 - 100..=x / 2 + 1 {
        let z = x - y;
        if z.abs_diff(y) > 100 {
            continue;
        }

        let p = min_stamps_for(STAMPS.len() as u8, y);
        let q = min_stamps_for(STAMPS.len() as u8, z);

        if p + q < lo {
            lo = p + q;
            result = (p, q)
        }
    }

    result
}

fn main() {
    let xs: Vec<u32> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().parse().unwrap())
        .collect();

    let sps = xs.into_iter().map(optimal_split).collect::<Vec<_>>();
    eprintln!("{:?}", sps);

    let result: u32 = sps.into_iter().map(|(a, b)| a + b).sum();
    println!("{}", result);
}
