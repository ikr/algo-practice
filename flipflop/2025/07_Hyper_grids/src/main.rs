use itertools::Itertools;
use memoize::memoize;
use std::io::{BufRead, stdin};

#[memoize]
fn num_ways(p: Vec<u8>) -> u64 {
    if p.iter().all(|&x| x == 0) {
        1
    } else {
        (0..p.len())
            .filter_map(|i| {
                if p[i] == 0 {
                    None
                } else {
                    let mut q = p.clone();
                    q[i] -= 1;
                    Some(num_ways(q))
                }
            })
            .sum()
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let dims: Vec<(usize, u8)> = lines
        .into_iter()
        .map(|s| {
            let (n, hi) = s
                .split(' ')
                .map(|sub| sub.parse().unwrap())
                .collect_tuple()
                .unwrap();
            (n, hi as u8)
        })
        .collect();

    let result: u64 = dims
        .into_iter()
        .map(|(n, hi)| num_ways(vec![hi - 1; n]))
        .sum();

    println!("{result}");
}
