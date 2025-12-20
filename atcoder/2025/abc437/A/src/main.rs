use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        a: i32,
        b: i32,
    }

    let result = a * 12 + b;
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
