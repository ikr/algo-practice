use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        m: usize,
    }

    for _ in 0..n.min(m) {
        writeln!(writer, "OK").unwrap();
    }

    for _ in m + 1..=n {
        writeln!(writer, "Too Many Requests").unwrap();
    }

    writer.flush().unwrap();
}
