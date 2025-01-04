use proconio::input;
use std::io::{self, BufWriter, Write};

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        a: usize,
        b: usize,
    }

    let result = (a + b).pow(2);
    writeln!(writer, "{}", result).unwrap();
    writer.flush().unwrap();
}
