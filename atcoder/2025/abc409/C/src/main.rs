use itertools::Itertools;
use proconio::input;
use std::{
    collections::HashMap,
    io::{BufWriter, Write, stdout},
};

fn solve(l: isize, xs: Vec<isize>) -> usize {
    if l % 3 == 0 {
        let d = l / 3;
        let fq: HashMap<isize, usize> = xs.into_iter().counts();
        let mut result = 0;
        for (x1, f1) in fq.iter() {
            let x0 = ((x1 - d) + l) % l;
            let x2 = (x1 + d) % l;

            if let Some(f0) = fq.get(&x0) {
                if let Some(f2) = fq.get(&x2) {
                    result += f0 * f1 * f2;
                }
            }
        }
        result / 3
    } else {
        0
    }
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        l: isize,
        ds: [isize; n - 1],
    }

    let mut xs: Vec<isize> = Vec::with_capacity(n);
    xs.push(0);
    for d in ds {
        if let Some(x) = xs.last() {
            xs.push((x + d) % l);
        }
    }

    let result = solve(l, xs);
    writeln!(writer, "{}", result).unwrap();
    writer.flush().unwrap();
}
