use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: i32,
        k: i32,
    }

    let result: i32 = (0..k)
        .find(|m| m * m + (2 * n + 1) * m + 2 * n >= 2 * k)
        .unwrap();
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
