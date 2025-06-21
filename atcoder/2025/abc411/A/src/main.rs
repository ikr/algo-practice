use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn solve(xs: String, l: usize) -> bool {
    xs.chars().count() >= l
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        xs: String,
        l: usize,
    }

    let result = solve(xs, l);
    writeln!(writer, "{}", if result { "Yes" } else { "No" }).unwrap();
    writer.flush().unwrap();
}
