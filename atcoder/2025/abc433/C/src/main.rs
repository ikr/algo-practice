use itertools::Itertools;
use proconio::input;
use proconio::marker::Bytes;
use std::io::{BufWriter, Write, stdout};

fn run_length_encoding(xs: Vec<u8>) -> Vec<(u8, usize)> {
    let mut result: Vec<(u8, usize)> = vec![(xs[0], 1)];
    for &x in &xs[1..] {
        if x == result.last().unwrap().0 {
            result.last_mut().unwrap().1 += 1;
        } else {
            result.push((x, 1));
        }
    }
    result
}

fn number_of_1122_substrings(xs: Vec<u8>) -> usize {
    let rle = run_length_encoding(xs);

    rle.into_iter()
        .tuple_windows()
        .filter_map(|((x1, f1), (x2, f2))| if x1 + 1 == x2 { Some((f1, f2)) } else { None })
        .map(|(f1, f2)| f1.min(f2))
        .sum()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        xs: Bytes,
    }

    let result = number_of_1122_substrings(xs);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
