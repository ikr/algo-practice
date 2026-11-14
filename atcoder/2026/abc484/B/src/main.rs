use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn solve(xs: Vec<i32>) -> i32 {
    if xs.contains(&9) {
        xs.into_iter().min().unwrap()
    } else {
        -1
    }
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
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
