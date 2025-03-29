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
    let g: Vec<Vec<usize>> = lines
        .into_iter()
        .fold(vec![vec![]; n], |mut acc, (u, v, _)| {
            acc[idx[&u]].push(idx[&v]);
            acc
        });
}
