use proconio::input;
use proconio::marker::Bytes;
use std::io::{BufWriter, Write, stdout};

fn both_want(t: Vec<u8>, a: Vec<u8>) -> bool {
    t.into_iter()
        .zip(a.iter())
        .any(|(x, y)| x == *y && x == b'o')
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        t: Bytes,
        a: Bytes,
    }
    assert_eq!(t.len(), n);

    let result = both_want(t, a);
    writeln!(writer, "{}", if result { "Yes" } else { "No" }).unwrap();
    writer.flush().unwrap();
}
