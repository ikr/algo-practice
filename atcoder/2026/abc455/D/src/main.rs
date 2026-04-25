use itertools::Itertools;
use proconio::{input, marker::Usize1};
use std::io::{BufWriter, Write, stdout};

const INF: usize = 1_000_000_000;

fn path_length_from(g: &[usize], u0: usize) -> usize {
    let mut result = 0;
    let mut u = u0;

    while u != INF {
        u = g[u];
        result += 1;
    }

    result - 1
}

fn stack_heights(n: usize, ops: Vec<(usize, usize)>) -> Vec<usize> {
    let mut g: Vec<usize> = vec![INF; 2 * n];
    let mut h: Vec<usize> = vec![INF; 2 * n];

    for u in 0..n {
        g[n + u] = u;
        h[u] = n + u;
    }

    for (c, p) in ops {
        assert_eq!(g[p], INF);
        g[p] = c;

        assert_eq!(g[h[c]], c);
        g[h[c]] = INF;
        h[c] = p;
    }

    (n..2 * n).map(|u| path_length_from(&g, u)).collect()
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
