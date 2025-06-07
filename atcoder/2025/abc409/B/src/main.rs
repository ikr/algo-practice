use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn solve(mut xs: Vec<usize>) -> usize {
    xs.sort();
    let n = xs.len();
    let mut result = 0;

    for (i, &x) in xs.iter().enumerate() {
        let tail_len = n - i;
        if (i == 0 || xs[i - 1] != xs[i]) && tail_len >= x {
            result = result.max(x);
        }
    }

    for i in 1..=n {
        if i <= xs[0] {
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
