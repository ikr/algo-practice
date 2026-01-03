use proconio::input;
use std::{
    io::{BufWriter, Write, stdout},
    iter::successors,
};

fn digit_squares(x0: u64) -> u64 {
    successors(Some(x0), |&x| (x != 0).then_some(x / 10))
        .map(|x| (x % 10).pow(2))
        .sum()
}

fn is_happy(x: u64) -> bool {
    successors(Some(x), |&x| Some(digit_squares(x)))
        .take(1000)
        .last()
        .unwrap()
        == 1
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        x: u64,
    }

    let result = if is_happy(x) { "Yes" } else { "No" };
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
