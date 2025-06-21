use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn sums_from(xs: &[i32], i: usize) -> Vec<i32> {
    xs.iter()
        .skip(i)
        .scan(0, |acc, x| {
            *acc += x;
            Some(*acc)
        })
        .collect()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        xs: [i32; n-1],
    }

    for i in 0..n - 1 {
        let result = sums_from(&xs, i)
            .into_iter()
            .map(|x| x.to_string())
            .collect::<Vec<_>>()
            .join(" ");
        writeln!(writer, "{}", result).unwrap();
    }

    writer.flush().unwrap();
}
