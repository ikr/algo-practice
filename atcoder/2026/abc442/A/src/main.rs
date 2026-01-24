use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        s: String,
    }

    let result: usize = s
        .chars()
        .into_iter()
        .map(|c| if c == 'i' || c == 'j' { 1 } else { 0 })
        .sum();
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
