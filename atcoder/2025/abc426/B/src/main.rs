use itertools::Itertools;
use proconio::input;
use proconio::marker::Bytes;
use std::io::{BufWriter, Write, stdout};

fn minority(xs: Vec<u8>) -> u8 {
    let fq = xs.into_iter().counts();
    fq.into_iter().find(|(_, f)| *f == 1).unwrap().0
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        xs: Bytes,
    }

    let result = minority(xs) as char;
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
