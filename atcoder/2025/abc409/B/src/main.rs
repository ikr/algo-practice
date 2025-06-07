use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn solve(mut xs: Vec<usize>) -> usize {
    xs.sort();
    let n = xs.len();
    let mut result = if xs[0] <= n { xs[0] } else { 0 };

    for (i, xx) in xs.windows(2).enumerate() {
        let tail_len = n - i - 1;
        if xx[0] != xx[1] && tail_len >= xx[1] {
            result = result.max(xx[1]);
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
