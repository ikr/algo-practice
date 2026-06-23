use proconio::input;
use std::{
    io::{BufWriter, Write, stdout},
    u32,
};

fn lowest_k_gap(lrs: Vec<(u32, u32)>, k: usize) -> Option<u32> {
    todo!()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        k: usize,
        lrs: [(u32, u32); n],
    }

    let result = match lowest_k_gap(lrs, k) {
        Some(a) => a.to_string(),
        None => "-1".to_string(),
    };
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
