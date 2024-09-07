use std::io::{self, BufRead};

use itertools::Itertools;

fn group_by_bitmask(xs: &[u8], bits: u32) -> (Vec<u8>, Vec<u8>) {
    let mut on = vec![];
    let mut off = vec![];

    xs.iter().enumerate().for_each(|(i, x)| {
        if (1 << i) & bits == 0 {
            off.push(*x);
        } else {
            on.push(*x);
        }
    });

    (on, off)
}

fn all_but(xs: &[u8], ys: &[u8]) -> Vec<u8> {
    xs.iter().cloned().filter(|x| !ys.contains(x)).collect()
}

fn u16sum(xs: &[u8]) -> u16 {
    xs.iter().map(|x| *x as u16).sum()
}

fn solve_part_1(xs: &[u8]) -> u64 {
    let n = xs.len();
    let mut result = u64::MAX;
    for k in 1..n - 1 {
        eprintln!("k:{}", k);

        for aa in xs.iter().combinations(k) {
            let a: Vec<u8> = aa.into_iter().cloned().collect();
            let sa = u16sum(&a);
            let ys: Vec<u8> = all_but(&xs, &a);
            if u16sum(&ys) != 2 * sa {
                continue;
            }

            let m = ys.len();
            eprintln!("a:{:?} bits:{}..{}", a, 0, 1 << m);

            for bits in 0..(1 << m) {
                let (b, c) = group_by_bitmask(&ys, bits);
                let sb = u16sum(&b);
                let sc = u16sum(&c);

                if sa == sb && sa == sc {
                    result = result.min(a.iter().fold(1u64, |acc, y| acc * (*y as u64)));
                }
            }
        }

        if result != u64::MAX {
            break;
        }
    }
    result
}

fn main() {
    let xs: Vec<u8> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().parse().unwrap())
        .collect();

    println!("{}", solve_part_1(&xs));
}
