use std::{
    collections::{BTreeSet, HashMap},
    io::{BufRead, stdin},
};

use itertools::Itertools;

const INF: u32 = 1_000_000_000;

fn parse_line(s: &str) -> (String, String, u32) {
    let ab: Vec<_> = s.split(" | ").collect();
    let cd: Vec<_> = ab[0].split(" -> ").collect();
    (cd[0].to_string(), cd[1].to_string(), ab[1].parse().unwrap())
}

fn main() {
    let lines: Vec<_> = stdin()
        .lock()
        .lines()
        .map(|line| parse_line(&line.unwrap()))
        .collect();

    let idx: HashMap<String, usize> =
        lines
            .iter()
            .flat_map(|(u, v, _)| vec![u, v])
            .fold(HashMap::new(), |mut acc, u| {
                let n = acc.len();
                acc.entry(u.to_string()).or_insert(n);
                acc
            });

    let n = idx.len();
    let g: Vec<Vec<(usize, u32)>> =
        lines
            .into_iter()
            .fold(vec![vec![]; n], |mut acc, (u, v, w)| {
                acc[idx[&u]].push((idx[&v], w));
                acc
            });

    let mut dist: Vec<u32> = vec![INF; n];
    dist[idx["STT"]] = 0;
    let mut q: BTreeSet<(u32, usize)> = BTreeSet::from([(0, idx["STT"])]);

    while let Some((w0, u0)) = q.pop_first() {
        for &(v, w) in g[u0].iter() {
            if w0 + w < dist[v] {
                q.remove(&(dist[v], v));
                dist[v] = w0 + w;
                q.insert((dist[v], v));
            }
        }
    }

    println!(
        "{}",
        dist.into_iter()
            .filter(|&d| d != INF)
            .k_largest(3)
            .product::<u32>()
    );
}
