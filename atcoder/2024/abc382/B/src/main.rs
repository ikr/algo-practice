use proconio::input;
use proconio::marker::Bytes;
use std::io::{self, BufWriter, Write};

fn solve(d: usize, xs: &[u8]) -> String {
    let mut cookie_indices: Vec<usize> = xs.iter().enumerate().fold(vec![], |mut acc, (i, &x)| {
        if x == b'@' {
            acc.push(i)
        }
        acc
    });

    let mut result: Vec<u8> = xs.to_vec();
    for _ in 0..d {
        let i = cookie_indices.pop().unwrap();
        result[i] = b'.';
    }
    String::from_utf8(result).unwrap()
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        _: usize,
        d: usize,
        xs: Bytes,
    }

    let result = solve(d, &xs);
    writeln!(writer, "{}", result).unwrap();
    writer.flush().unwrap();
}
