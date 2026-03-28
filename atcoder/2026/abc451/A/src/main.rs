use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        s: String,
    }

    let n = s.len();
    let result = if n % 5 == 0 { "Yes" } else { "No" };
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
