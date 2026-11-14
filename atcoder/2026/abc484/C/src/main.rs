use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn is_possible(xs: Vec<i32>, ys: Vec<i32>) -> bool {
    let n = xs.len();
    assert_eq!(ys.len(), n);

    let mb_i = (0..n).find(|&i| xs[i] != ys[i]);
    let mb_j = (0..n).rev().find(|&i| xs[i] != ys[i]);

    match (mb_i, mb_j) {
        (Some(i), Some(j)) => {
            let mut a = xs.clone();
            let a0 = a[j];
            a.remove(j);
            a.insert(i, a0);

            let mut b = xs.clone();
            let b0 = b[i];
            b.remove(i);
            b.insert(j, b0);

            a == ys || b == ys
        }
        (None, None) => true,
        _ => unreachable!(),
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
