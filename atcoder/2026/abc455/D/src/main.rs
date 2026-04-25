use itertools::Itertools;
use proconio::{input, marker::Usize1};
use std::io::{BufWriter, Write, stdout};

fn stack_heights(n: usize, ops: Vec<(usize, usize)>) -> Vec<usize> {
    let mut g: Vec<Vec<usize>> = vec![vec![]; 2 * n];

    for u in 0..n {
        g[u].push(n + u);
        g[n + u].push(u);
    }

    for (c, p) in ops {}

    todo!()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        q: usize,
        ops: [(Usize1, Usize1); q],
    }

    let result = stack_heights(n, ops).into_iter().join(" ");
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
