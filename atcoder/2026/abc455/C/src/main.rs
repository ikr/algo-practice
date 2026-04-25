use itertools::Itertools;
use proconio::input;
use std::{
    collections::BinaryHeap,
    io::{BufWriter, Write, stdout},
};

fn min_sum(xs: Vec<u64>, mut k: usize) -> u64 {
    let mut pq: BinaryHeap<(u64, usize)> = xs.into_iter().counts().into_iter().collect();

    while let Some((x, f)) = pq.pop()
        && k != 0
    {
        let delta = f.min(k);
        k -= delta;

        if delta < f {
            pq.push((x, f - delta));
        } else {
            assert_eq!(delta, f);
        }
    }

    todo!()
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
