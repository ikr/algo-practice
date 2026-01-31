use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        mut s: String,
    }

    s.push('s');
    writeln!(writer, "{s}").unwrap();
    writer.flush().unwrap();
}
