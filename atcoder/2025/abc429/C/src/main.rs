use itertools::Itertools;
use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn proper_triples_count(xs: Vec<usize>) -> usize {
    let n = xs.len();
    let fq = xs.into_iter().counts();

    fq.into_values()
        .map(|f| {
            if f >= 2 {
                let pairs = f * (f - 1) / 2;
                let others = n - f;
                pairs * others
            } else {
                0
            }
        })
        .sum()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        xs: [usize; n],
    }

    let result = proper_triples_count(xs);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
