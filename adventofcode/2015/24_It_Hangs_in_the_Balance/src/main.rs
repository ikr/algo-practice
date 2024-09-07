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

fn is_splittable_in_two_having_given_sum_each(xs: &[u8], s: u16) -> bool {
    let m = xs.len();
    (0..(1 << m)).any(|bits| {
        let (a, b) = group_by_bitmask(&xs, bits);
        let sa = u16sum(&a);
        let sb = u16sum(&b);
        s == sa && s == sb
    })
}

fn solve_part_1(xs: &[u8]) -> u64 {
    let n = xs.len();
    let mut result = u64::MAX;
    for k in 1..n - 1 {
        for aa in xs.iter().combinations(k) {
            let a: Vec<u8> = aa.into_iter().cloned().collect();
            let sa = u16sum(&a);
            let ys: Vec<u8> = all_but(&xs, &a);
            if u16sum(&ys) != 2 * sa {
                continue;
            }

            if is_splittable_in_two_having_given_sum_each(&ys, sa) {
                result = result.min(a.iter().fold(1u64, |acc, y| acc * (*y as u64)));
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
