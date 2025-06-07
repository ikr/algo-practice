use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn solve(mut xs: Vec<usize>) -> usize {
    xs.sort();
    let n = xs.len();
    let mut result = 0;

    for i in 1..=n {
        let p = xs.partition_point(|&x| x < i);
        let tail_len = n - p;
        if i <= tail_len {
            result = result.max(i);
        }
    }

    result
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        xs: [usize; n],
    }

    let result = solve(xs);
    writeln!(writer, "{}", result).unwrap();
    writer.flush().unwrap();
}
