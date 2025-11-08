use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        h: i8,
        b: i8,
    }

    let result = if h > b { h - b } else { 0 };
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
