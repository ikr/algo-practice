use std::io::{stdout, BufWriter, Write};
use proconio::input;
// use proconio::marker::Bytes;

fn solve(xs: Vec<i32>) -> i32 {
    xs.into_iter().sum::<i32>()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        xs: [i32; n],
    }

    let result = solve(xs);
    writeln!(writer, "{}", result).unwrap();
    writer.flush().unwrap();
}
