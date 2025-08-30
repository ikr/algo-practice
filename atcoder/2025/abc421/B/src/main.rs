use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn digits_reversed(mut x: u64) -> Vec<u64> {
    let mut ans = vec![];
    while x != 0 {
        ans.push(x % 10);
        x /= 10;
    }
    ans
}

fn number(ds: Vec<u64>) -> u64 {
    if ds.is_empty() {
        0
    } else {
        let mut ans = 0;
        let mut mul = 1;

        for d in ds.into_iter().rev() {
            ans += d * mul;
            mul *= 10;
        }

        ans
    }
}

fn compute_next(x: u64, y: u64) -> u64 {
    number(digits_reversed(x + y))
}

fn compute_a10(a1: u64, a2: u64) -> u64 {
    let mut x = a1;
    let mut y = a2;
    let mut z = compute_next(x, y);

    for _ in 4..=10 {
        (x, y) = (y, z);
        z = compute_next(x, y);
    }
    z
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        a1: u64,
        a2: u64,
    }

    let result = compute_a10(a1, a2);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
