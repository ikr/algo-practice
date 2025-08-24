use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        x: u8,
        y: u8,
    }

    let result = ((x + y - 1) % 12) + 1;
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
