use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn is_possible(xs: Vec<i32>, ys: Vec<i32>) -> bool {
    let n = xs.len();
    assert_eq!(ys.len(), n);

    let ii: Vec<usize> = (0..n).filter(|&i| xs[i] != ys[i]).collect();
    match ii[..] {
        [] => true,
        [i, j] => xs[i] == ys[j] && xs[j] == ys[i],
        _ => false,
    }
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        xs: [i32; n],
        ys: [i32; n],
    }

    let result = if is_possible(xs, ys) { "Yes" } else { "No" };
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
