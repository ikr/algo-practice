use std::collections::VecDeque;

use proconio::{input, marker::Usize1};

const INF: usize = 1_000_000_007;

fn all_ditstances(g: &[Vec<usize>], u0: usize) -> Vec<usize> {
    let mut ds: Vec<usize> = vec![INF; g.len()];
    ds[u0] = 0;
    let mut q = VecDeque::from([u0]);

    while let Some(u) = q.pop_front() {
        for &v in &g[u] {
            if ds[v] == INF {
                ds[v] = ds[u] + 1;
                q.push_back(v);
            }
        }
    }

    ds
}

fn graph_from_edges(n: usize, edges: &[(usize, usize)]) -> Vec<Vec<usize>> {
    edges.iter().fold(vec![vec![]; n], |mut agg, &(u, v)| {
        agg[u].push(v);
        agg[v].push(u);
        agg
    })
}

fn main() {
    input! {
        _: String,
        n: usize,
        edges: [(Usize1, Usize1); 2]
    }

    let ring_edges: Vec<(usize, usize)> = (0..n).map(|u| (u, (u + 1) % n)).collect();
    let ring = graph_from_edges(n, &ring_edges);
    let full_graph = graph_from_edges(n, &ring_edges.into_iter().chain(edges).collect::<Vec<_>>());

    let ab: Vec<usize> = [ring, full_graph]
        .into_iter()
        .map(|g| {
            let d_sums: Vec<usize> = (0..n)
                .map(|u| all_ditstances(&g, u).into_iter().sum::<usize>())
                .collect();
            d_sums.into_iter().sum()
        })
        .collect();

    let result = ab[0] - ab[1];
    println!("{result}");
}
