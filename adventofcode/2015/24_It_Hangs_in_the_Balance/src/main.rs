use std::io::{self, BufRead};

use itertools::Itertools;

fn group_by_bitmask(xs: &[i16], bits: i16) -> (Vec<i16>, Vec<i16>) {
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

fn all_but(xs: &[i16], ys: &[i16]) -> Vec<i16> {
    xs.iter().cloned().filter(|x| !ys.contains(x)).collect()
}

fn main() {
    let xs: Vec<i16> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().parse().unwrap())
        .collect();

    let n = xs.len();
    let mut result = i64::MAX;
    for k in 1..n - 1 {
        eprintln!("k:{}", k);

        for aa in xs.iter().combinations(k) {
            let a: Vec<i16> = aa.into_iter().cloned().collect();
            let sa = a.iter().sum::<i16>();
            let ys: Vec<i16> = all_but(&xs, &a);
            if ys.iter().sum::<i16>() != 2 * sa {
                continue;
            }

            let m = ys.len();
            eprintln!("a:{:?} bits:{}..{}", a, 0, 1 << m);

            for bits in 0..(1 << m) {
                let (b, c) = group_by_bitmask(&ys, bits);
                let sb = b.into_iter().sum::<i16>();
                let sc = c.into_iter().sum::<i16>();

                if sa == sb && sa == sc {
                    result = result.min(a.iter().fold(1i64, |acc, y| acc * (*y as i64)));
                }
            }
        }

        if result != i64::MAX {
            break;
        }
    }

    println!("{}", result);
}
