use std::{
    collections::{HashMap, VecDeque},
    io::{BufRead, stdin},
};

use itertools::Itertools;

const INF: u16 = 30000;

fn parse_line(s: &str) -> (String, String, u16) {
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
    let g: Vec<Vec<usize>> = lines
        .into_iter()
        .fold(vec![vec![]; n], |mut acc, (u, v, _)| {
            acc[idx[&u]].push(idx[&v]);
            acc
        });

    let mut dist: Vec<u16> = vec![INF; n];
    dist[idx["STT"]] = 0;
    let mut q = VecDeque::from([idx["STT"]]);

    while let Some(u) = q.pop_front() {
        for &v in g[u].iter() {
            if dist[v] == INF {
                dist[v] = dist[u] + 1;
                q.push_back(v);
            }
        }
    }

    println!(
        "{}",
        dist.into_iter()
            .filter(|&d| d != INF)
            .k_largest(3)
            .product::<u16>()
    );
}
