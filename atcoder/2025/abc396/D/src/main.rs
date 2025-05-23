use itertools::Itertools;
use proconio::input;
use proconio::marker::Usize1;
use std::{
    collections::HashMap,
    io::{self, BufWriter, Write},
};

fn path_xor(es: &HashMap<(usize, usize), u64>, ii: &[usize]) -> u64 {
    ii.windows(2)
        .map(|ab| *es.get(&(ab[0], ab[1])).unwrap())
        .fold(0, |acc, x| acc ^ x)
}

fn min_paths_xor(n: usize, es: HashMap<(usize, usize), u64>) -> u64 {
    let inners: Vec<usize> = (1..(n - 1)).collect();
    let mut result = u64::MAX;

    for inner in inners.into_iter().powerset() {
        let inner_len: usize = inner.len();
        let walkable_inners: Vec<Vec<usize>> = inner
            .into_iter()
            .permutations(inner_len)
            .map(|ii| {
                let mut result: Vec<usize> = vec![0];
                result.extend(ii);
                result.push(n - 1);
                result
            })
            .filter(|ii| {
                ii.windows(2).all(|ab| {
                    let a: usize = ab[0];
                    let b: usize = ab[1];
                    es.contains_key(&(a, b))
                })
            })
            .collect();

        for ii in walkable_inners {
            result = result.min(path_xor(&es, &ii));
        }
    }

    result
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        m: usize,
        edges: [(Usize1, Usize1, u64); m],
    }

    let mut es: HashMap<(usize, usize), u64> = HashMap::new();

    for (u, v, w) in edges {
        es.insert((u, v), w);
        es.insert((v, u), w);
    }

    let result = min_paths_xor(n, es);
    writeln!(writer, "{}", result).unwrap();
    writer.flush().unwrap();
}
