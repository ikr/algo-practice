use proconio::input;
use proconio::marker::Bytes;
use std::io::{BufWriter, Write, stdout};

fn digit_distance(src: u8, dst: u8) -> usize {
    (if src <= dst {
        dst - src
    } else {
        10 - src + dst
    }) as usize
}

fn distance(a: &[u8], b: &[u8]) -> usize {
    assert_eq!(a.len(), b.len());
    a.iter().zip(b).map(|(&x, &y)| digit_distance(x, y)).sum()
}

fn min_ops(haystack: Vec<u8>, needle: Vec<u8>) -> usize {
    haystack
        .windows(needle.len())
        .map(|sub| distance(&needle, sub))
        .min()
        .unwrap()
}

fn digit_values(xs: Vec<u8>) -> Vec<u8> {
    xs.into_iter().map(|x| x - b'0').collect()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        m: usize,
        haystack: Bytes,
        needle: Bytes,
    }
    assert_eq!(haystack.len(), n);
    assert_eq!(needle.len(), m);

    let result = min_ops(digit_values(haystack), digit_values(needle));
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
