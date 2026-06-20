use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        x: u32,
        y: u32,
    }

    let result = if 9 * x == 16 * y { "Yes" } else { "No" };
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
