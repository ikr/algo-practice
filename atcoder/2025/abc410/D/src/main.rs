use proconio::{input, marker::Usize1};
use std::{
    collections::VecDeque,
    i16,
    io::{BufWriter, Write, stdout},
};

#[derive(Clone, Copy)]
struct Edge(usize, i16);

#[derive(Clone, Copy)]
struct Walk {
    hops: usize,
    u: usize,
    xor_acc: i16,
}

impl Walk {
    fn new(u: usize, xor_acc: i16) -> Self {
        Self {
            hops: 0,
            u,
            xor_acc,
        }
    }

    fn hop(self, e: Edge) -> Self {
        let hops = self.hops + 1;
        let u = e.0;
        let xor_acc = self.xor_acc ^ e.1;
        Self { hops, u, xor_acc }
    }
}

fn graph_from(n: usize, edges: Vec<(usize, usize, i16)>) -> Vec<Vec<Edge>> {
    edges
        .into_iter()
        .fold(vec![vec![]; n], |mut acc, (u, v, w)| {
            acc[u].push(Edge(v, w));
            acc
        })
}

fn min_walk_xor(n: usize, edges: Vec<(usize, usize, i16)>) -> i16 {
    let m = edges.len();
    let g = graph_from(n, edges);
    let mut q: VecDeque<Walk> = VecDeque::from([Walk::new(0, 0)]);
    let mut result = i16::MAX;

    while let Some(walk) = q.pop_front() {
        if walk.u == n - 1 {
            result = result.min(walk.xor_acc);
        }

        if walk.hops < m {
            for &e in g[walk.u].iter() {
                q.push_back(walk.hop(e))
            }
        }
    }

    if result == i16::MAX { -1 } else { result }
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
