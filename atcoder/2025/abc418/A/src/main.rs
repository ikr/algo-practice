use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn solve(xs: String) -> bool {
    xs.ends_with("tea")
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        xs: String,
    }
    assert_eq!(xs.len(), n);

    let result = if solve(xs) { "Yes" } else { "No" };
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
