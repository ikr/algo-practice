use proconio::{input, marker::Usize1};
use std::io::{BufWriter, Write, stdout};

fn min_walk_xor(n: usize, edges: Vec<(usize, usize, i16)>) -> i16 {
    let mut d = vec![i16::MAX; n];
    d[0] = 0;

    for _ in 0..n {
        for &(u, v, w) in edges.iter() {
            if d[u] != i16::MAX {
                d[v] = d[v].min(d[u] ^ w);
            }
        }
    }

    if d[n - 1] == i16::MAX { -1 } else { d[n - 1] }
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        m: usize,
        edges: [(Usize1, Usize1, i16); m],
    }

    let result = min_walk_xor(n, edges);
    writeln!(writer, "{}", result).unwrap();
    writer.flush().unwrap();
}
