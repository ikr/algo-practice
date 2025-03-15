use proconio::input;
use std::{
    collections::HashSet,
    io::{self, BufWriter, Write},
};

const MIO: u64 = 1_000_000;

fn all_cubes() -> Vec<u64> {
    (0..=MIO).map(|i| i * i * i).collect()
}

fn solve(n: u64) -> Option<(u64, u64)> {
    let qs = all_cubes();
    let qss: HashSet<u64> = qs.iter().copied().collect();

    for (y, y_3) in qs.iter().enumerate().skip(1) {
        if qss.contains(&(y_3 + n)) {
            let x = qs.binary_search(&(y_3 + n)).unwrap();
            return Some((x as u64, y as u64));
        }
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
