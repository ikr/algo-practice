use proconio::input;
use std::io::{self, BufWriter, Write};

const MIO: u128 = 1_000_000;
const N_MAX: usize = 1_000_000 * 1_000_000 * 1_000_000;

fn all_cubes() -> Vec<u128> {
    (0..=MIO).map(|i| i * i * i).collect()
}

fn foo(y: usize) -> usize {
    3 * y * y + 3 * y + 1
}

fn all_yys() -> Vec<usize> {
    let mut result: Vec<usize> = vec![];
    while foo(result.len()) <= N_MAX {
        let y = result.len();
        result.push(foo(y));
    }
    result
}

fn solve(n: u64) -> Option<(u64, u64)> {
    if n == 1 {
        return None;
    }
    let qs = all_cubes();

    for (y, y_3) in qs.iter().enumerate().skip(1) {
        if let Ok(x) = qs.binary_search(&(y_3 + n as u128)) {
            return Some((x as u64, y as u64));
        }
    }

    let yys = all_yys();
    if let Ok(y) = yys.binary_search(&(n as usize)) {
        return Some((y as u64 + 1, y as u64));
    }

    None
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: u64,
    }

    if let Some((x, y)) = solve(n) {
        writeln!(writer, "{} {}", x, y).unwrap();
    } else {
        writeln!(writer, "-1").unwrap();
    }
    writer.flush().unwrap();
}
