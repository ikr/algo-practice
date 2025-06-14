use proconio::input;
use std::io::{BufWriter, Write, stdout};
// use proconio::marker::Bytes;

fn solve(xs: &[i32], k: i32) -> usize {
    xs.iter().filter(|x| k <= **x).count()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        a: [i32; n],
        k: i32
    }

    let result = solve(&a, k);
    writeln!(writer, "{}", result).unwrap();
    writer.flush().unwrap();
}
