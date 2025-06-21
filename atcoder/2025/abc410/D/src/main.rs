use proconio::{input, marker::Usize1};
use std::{
    collections::VecDeque,
    io::{BufWriter, Write, stdout},
};

const BASE: usize = 1 << 10;

#[derive(Clone, Copy)]
struct Edge {
    dest: usize,
    weight: usize,
}

impl Edge {
    fn new(dest: usize, weight: usize) -> Self {
        Self { dest, weight }
    }
}

fn graph_from(n: usize, edges: Vec<(usize, usize, usize)>) -> Vec<Vec<Edge>> {
    edges
        .into_iter()
        .fold(vec![vec![]; n], |mut acc, (u, v, w)| {
            acc[u].push(Edge::new(v, w));
            acc
        })
}

fn min_walk_xor(n: usize, edges: Vec<(usize, usize, usize)>) -> isize {
    let g = graph_from(n, edges);

    let mut done: Vec<bool> = vec![false; BASE * BASE];
    done[0] = true;
    let mut result: usize = usize::MAX;

    let mut q: VecDeque<usize> = VecDeque::from([0]);
    while let Some(ueber_u) = q.pop_front() {
        let u = ueber_u / BASE;
        let acc = ueber_u % BASE;

        for &Edge { dest, weight } in g[u].iter() {
            let ueber_v = dest * BASE + (acc ^ weight);
            if dest == n - 1 {
                result = result.min(acc ^ weight);
            }

            if !done[ueber_v] {
                q.push_back(ueber_v);
                done[ueber_v] = true;
            }
        }
    }

    if result == usize::MAX {
        -1
    } else {
        result as isize
    }
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        m: usize,
        edges: [(Usize1, Usize1, usize); m],
    }

    let result = min_walk_xor(n, edges);
    writeln!(writer, "{}", result).unwrap();
    writer.flush().unwrap();
}
