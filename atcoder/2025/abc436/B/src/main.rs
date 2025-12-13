use itertools::Itertools;
use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn construct_magic_square(n: usize) -> Vec<Vec<usize>> {
    let mut result = vec![vec![0; n]; n];
    let mut ro = 0;
    let mut co = (n - 1) / 2;
    let mut k = 1;
    result[ro][co] = k;

    for _ in 0..n * n - 1 {
        k += 1;

        if result[(n + ro - 1) % n][(co + 1) % n] == 0 {
            ro = (n + ro - 1) % n;
            co = (co + 1) % n;
        } else {
            ro = (ro + 1) % n;
        }

        result[ro][co] = k;
    }

    result
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
    }

    let result = construct_magic_square(n);
    for row in result {
        writeln!(writer, "{}", row.into_iter().join(" ")).unwrap();
    }
    writer.flush().unwrap();
}
