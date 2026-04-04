use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        m: u8,
        d: u8,
    }

    let xs = [(1, 7), (3, 3), (5, 5), (7, 7), (9, 9)];

    let result = if xs.contains(&(m, d)) { "Yes" } else { "No" };
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
