use itertools::Itertools;
use proconio::input;
use std::io::{self, BufWriter, Write};

fn solve(xs: &[i32]) -> bool {
    let mut fs: Vec<usize> = xs.iter().cloned().counts().values().cloned().collect();

    if fs.len() < 2 {
        return false;
    }

    fs.sort();
    fs.reverse();
    fs[0] >= 3 && fs[1] >= 2
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        xs: [i32; 7],
    }

    let result = solve(&xs);
    writeln!(writer, "{}", if result { "Yes" } else { "No" }).unwrap();
    writer.flush().unwrap();
}
