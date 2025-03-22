use itertools::Itertools;
use proconio::input;
use std::io::{self, BufWriter, Write};

fn solve(xs: &[i32]) -> Option<usize> {
    let fq = xs.iter().cloned().counts();
    Some(
        xs.iter()
            .enumerate()
            .filter(|(_, x)| *fq.get(&x).unwrap() == 1)
            .map(|(i, x)| (i + 1, x))
            .max_by_key(|(_, x)| *x)?
            .0,
    )
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        xs: [i32; n],
    }

    let result = solve(&xs);
    writeln!(
        writer,
        "{}",
        match result {
            Some(i) => i.to_string(),
            None => "-1".to_string(),
        }
    )
    .unwrap();
    writer.flush().unwrap();
}
