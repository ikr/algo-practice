use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        a: u8,
        b: u8,
        c: u8,
        d: u8,
    }

    let result = if c >= a { d >= b } else { true };
    writeln!(writer, "{}", if !result { "Yes" } else { "No" }).unwrap();
    writer.flush().unwrap();
}
