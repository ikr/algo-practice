use itertools::Itertools;
use proconio::input;
use std::{
    collections::BinaryHeap,
    io::{BufWriter, Write, stdout},
};

fn is_satisfiable_in_k_ops(xs: &[u64], mut k: u64) -> bool {
    let mut pq: BinaryHeap<(u64, usize)> = xs
        .iter()
        .enumerate()
        .tuple_windows()
        .map(|((i, &x), (_, &y))| (x.abs_diff(y), i))
        .collect();

    todo!()
}

fn min_ops(xs: Vec<u64>) -> u64 {
    let mut lo: u64 = 0;

    if is_satisfiable_in_k_ops(&xs, lo) {
        return lo;
    }

    let mut hi: u64 = xs.len().pow(2) as u64;
    assert!(is_satisfiable_in_k_ops(&xs, hi));

    while lo + 1 < hi {
        let mid = lo + (hi - lo) / 2;
        if is_satisfiable_in_k_ops(&xs, mid) {
            hi = mid;
        } else {
            lo = mid;
        }
    }

    hi
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {t: u16}

    for _ in 0..t {
        input! {
            n: usize,
            xs: [u64; n],
        }

        let result = min_ops(xs);
        writeln!(writer, "{result}").unwrap();
    }

    writer.flush().unwrap();
}
