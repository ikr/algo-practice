use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: isize,
    }

    let result = (1 << n) - 2 * n;
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
