use proconio::input;
use proconio::marker::Bytes;
use std::io::{self, BufWriter, Write};

fn solve(n: usize, d: usize, xs: &[u8]) -> usize {
    let total_cookies = xs.iter().filter(|&&x| x == b'@').count();
    let initial_empty_boxes = n - total_cookies;
    initial_empty_boxes + d
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        d: usize,
        xs: Bytes,
    }

    let result = solve(n, d, &xs);
    writeln!(writer, "{}", result).unwrap();
    writer.flush().unwrap();
}
