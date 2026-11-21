use itertools::Itertools;
use proconio::{input, marker::Usize1};
use std::io::{BufWriter, Write, stdout};

fn distances_to_other_colors(cs: Vec<usize>) -> Vec<usize> {
    let n = cs.len();
    let mut idx: Vec<Vec<(usize, usize)>> = vec![vec![]; n];
    let mut i: usize = 0;

    for (j, &c) in cs.iter().enumerate() {
        if cs[i] != c {
            idx[cs[i]].push((i, j - 1));
            i = j;
        }
    }

    idx[cs[i]].push((i, n - 1));

    (0..n)
        .map(|i| {
            let c = cs[i];
            let j = idx[c].partition_point(|&(_, b)| b < i);

            match idx[c][j] {
                (0, b) => b + 1 - i,
                (a, b) if b == n - 1 => i - a + 1,
                (a, b) => (i - a + 1).min(b + 1 - i),
            }
        })
        .collect()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        cs: [Usize1; n],
    }

    let result = distances_to_other_colors(cs);
    writeln!(writer, "{}", result.into_iter().join(" ")).unwrap();
    writer.flush().unwrap();
}
