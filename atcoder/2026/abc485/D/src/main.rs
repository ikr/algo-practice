use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn num_ways(xs: Vec<u8>) -> usize {
    todo!()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        _n: usize,
        s: String,
    }

    let result = num_ways(s.bytes().map(|x| x - b'A').collect());
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
