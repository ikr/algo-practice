use proconio::input;
use proconio::marker::Bytes;
use std::{
    collections::HashSet,
    io::{BufWriter, Write, stdout},
    usize,
};

fn min_ops_one_side(xs: &[u8], target: u8) -> usize {
    if let Some(deepest_i) = xs.iter().rposition(|&x| x != target) {
        xs[..=deepest_i]
            .iter()
            .map(|&x| if x == target { 2 } else { 1 })
            .sum()
    } else {
        0
    }
}

fn div_ceil(x: usize, y: usize) -> usize {
    if x == 0 { 0 } else { 1 + (x - 1) / y }
}

fn min_ops(xs: &[u8], target: u8) -> usize {
    let n = xs.len();
    let mut result: usize = usize::MAX;
    for m in HashSet::from([n / 2, div_ceil(n, 2)]) {
        let a = &xs[..m];

        let mut b: Vec<u8> = xs[m..].to_vec();
        b.reverse();

        result = result.min(min_ops_one_side(a, target) + min_ops_one_side(&b, target));
    }
    result
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        t: u32,
    }

    for _ in 0..t {
        input! {
            n: usize,
            mut xs: Bytes,
        }
        assert_eq!(xs.len(), n);

        for x in &mut xs {
            *x -= b'0';
        }

        let mut result = usize::MAX;

        result = result.min(min_ops(&xs, 0));
        result = result.min(min_ops(&xs, 1));

        xs.reverse();

        result = result.min(min_ops(&xs, 0));
        result = result.min(min_ops(&xs, 1));

        writeln!(writer, "{result}").unwrap();
    }

    writer.flush().unwrap();
}
