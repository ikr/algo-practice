use proconio::{input, marker::Usize1};
use std::io::{BufWriter, Write, stdout};

fn num_triplets(n: usize) -> usize {
    if n < 3 { 0 } else { n * (n - 1) * (n - 2) / 6 }
}

fn num_reviewer_triples_by_author(g: Vec<Vec<usize>>) -> Vec<usize> {
    let n = g.len();
    (0..n)
        .map(|u| num_triplets(n.saturating_sub(g[u].len() + 1)))
        .collect()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        m: usize,
        edges: [(Usize1, Usize1); m],
    }

    let g: Vec<Vec<usize>> = edges.into_iter().fold(vec![vec![]; n], |mut acc, (u, v)| {
        acc[u].push(v);
        acc[v].push(u);
        acc
    });

    let result = num_reviewer_triples_by_author(g)
        .into_iter()
        .map(|x| x.to_string())
        .collect::<Vec<_>>()
        .join(" ");
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
