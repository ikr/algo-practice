use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        b: i32,
        r: i32,
    }

    let result = (30 - b) * (30 - r);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
