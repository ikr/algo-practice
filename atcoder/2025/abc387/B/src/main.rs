use proconio::input;
use std::io::{self, BufWriter, Write};

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        x: usize,
    }

    let mut total: usize = 0;
    for i in 1..=9 {
        for j in 1..=9 {
            if x != i * j {
                total += i * j;
            }
        }
    }

    writeln!(writer, "{}", total).unwrap();
    writer.flush().unwrap();
}
