use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        aa: [i64; 7],
        bb: [i64; 7],
    }

    let result: i64 = aa.into_iter().zip(bb).map(|(a, b)| a * b).sum();
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
