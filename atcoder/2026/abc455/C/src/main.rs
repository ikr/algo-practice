use itertools::Itertools;
use proconio::input;
use std::{
    collections::BinaryHeap,
    io::{BufWriter, Write, stdout},
};

fn min_sum(xs: Vec<u64>, k: usize) -> u64 {
    let mut pq: BinaryHeap<u64> = xs
        .into_iter()
        .counts()
        .into_iter()
        .map(|(x, f)| x * (f as u64))
        .collect();

    for _ in 0..k {
        pq.pop();
    }

    pq.into_iter().sum()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        k: usize,
        xs: [u64; n],
    }

    let result = min_sum(xs, k);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
