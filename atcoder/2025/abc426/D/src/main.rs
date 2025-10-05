use itertools::Itertools;
use proconio::input;
use proconio::marker::Bytes;
use std::io::{BufWriter, Write, stdout};

fn min_ops(xs: &[u8], target: u8) -> usize {
    let rle: Vec<(u8, usize)> = xs
        .iter()
        .chunk_by(|x| *x)
        .into_iter()
        .map(|(&x, xs)| (x, xs.count()))
        .collect();

    let hi: usize = rle
        .into_iter()
        .filter_map(|(x, k)| if x == target { Some(k) } else { None })
        .max()
        .unwrap_or_default();

    let n = xs.len();
    let a = xs.iter().filter(|&&x| x == target).count();
    let b = n - a;

    2 * (a - hi) + b
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

        writeln!(writer, "{result}").unwrap();
    }

    writer.flush().unwrap();
}
