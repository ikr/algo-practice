use proconio::{input, is_stdin_empty, marker::Usize1};
use std::collections::VecDeque;

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

fn graph_strain(g: &[Vec<usize>]) -> usize {
    let d_sums: Vec<usize> = (0..g.len())
        .map(|u| all_ditstances(g, u).into_iter().sum::<usize>())
        .collect();
    d_sums.into_iter().sum()
}

fn all_matching_variants<T: Copy + PartialEq>(xs: Vec<T>) -> Vec<Vec<(T, T)>> {
    assert_eq!(xs.len() % 2, 0);

    if let [a, b] = xs[..] {
        return vec![vec![(a, b)]];
    }

    let mut result: Vec<Vec<(T, T)>> = vec![];
    let a = xs[0];

    for &b in &xs[1..] {
        let ys: Vec<T> = xs[1..].iter().copied().filter(|&x| x != b).collect();
        let mut sub = all_matching_variants(ys);

        for matching in &mut sub {
            matching.push((a, b));
        }

        result.extend(sub);
    }

    result
}

fn main() {
    input! {
        _: String,
        n: usize,
    }

    let mut edges: Vec<(usize, usize)> = vec![];
    while !is_stdin_empty() {
        input! {
            u: Usize1,
            v: Usize1,
        }

        edges.push((u, v));
    }

    let ring_edges: Vec<(usize, usize)> = (0..n)
        .flat_map(|u| {
            (1..=3)
                .map(|delta| (u, (u + delta) % n))
                .collect::<Vec<_>>()
        })
        .collect();

    let ring = graph_from_edges(n, &ring_edges);
    let ring_strain = graph_strain(&ring);
    let full_graph = graph_from_edges(n, &ring_edges.into_iter().chain(edges).collect::<Vec<_>>());
    let tuning_offset = n / 8;

    let lo: usize = (0..n)
        .map(|u| {
            (0..8)
                .map(|i| (u + i * tuning_offset) % n)
                .collect::<Vec<usize>>()
        })
        .flat_map(all_matching_variants)
        .map(|edges| {
            let mut g = full_graph.clone();

            for (u, v) in edges {
                g[u].push(v);
                g[v].push(u);
            }

            graph_strain(&g)
        })
        .min()
        .unwrap();

    println!("{}", ring_strain - lo);
}
