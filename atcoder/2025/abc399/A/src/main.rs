use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        _: usize,
        s:String,
        t: String,
    }

    let result: usize = s
        .chars()
        .zip(t.chars())
        .map(|(a, b)| if a == b { 0 } else { 1 })
        .sum();
    writeln!(writer, "{}", result).unwrap();
    writer.flush().unwrap();
}
