use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn min_walk_xor(xs: Vec<i32>) -> i32 {
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

    let result = min_walk_xor(xs);
    writeln!(writer, "{}", result).unwrap();
    writer.flush().unwrap();
}
