use proconio::{input, marker::Bytes};
use std::io::{BufWriter, Write, stdout};

fn min_ops(xs: Vec<u8>) -> usize {
    let ones_idx: Vec<usize> = xs
        .into_iter()
        .enumerate()
        .filter_map(|(i, x)| if x == b'A' { Some(i) } else { None })
        .collect();

    let mut moves_to_even = 0;
    let mut moves_to_odd = 0;
    for (i, k) in ones_idx.into_iter().enumerate() {
        moves_to_even += k.abs_diff(2 * i);
        moves_to_odd += k.abs_diff(2 * i + 1);
    }
    moves_to_even.min(moves_to_odd)
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        xs: Bytes,
    }
    assert_eq!(xs.len(), 2 * n);

    let result = min_ops(xs);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
