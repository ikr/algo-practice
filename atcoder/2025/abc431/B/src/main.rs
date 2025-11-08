use proconio::input;
use proconio::marker::Usize1;
use std::io::{BufWriter, Write, stdout};

fn solve(xs: Vec<i32>) -> i32 {
    xs.into_iter().sum::<i32>()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        x: i32,
        n: usize,
        ws: [i32; n],
        q: usize,
        ii: [Usize1; q],
    }

    let mut cur = x;
    let mut present = vec![false; n];
    for i in ii {
        if present[i] {
            cur -= ws[i];
        } else {
            cur += ws[i];
        }
        present[i] = !present[i];
        writeln!(writer, "{cur}").unwrap();
    }

    writer.flush().unwrap();
}
