use proconio::{input, marker::Usize1};
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        q: usize,
        queries:[(u8, Usize1); q],
    }

    for (t, i) in queries {}

    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
