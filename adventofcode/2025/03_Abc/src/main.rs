use itertools::Itertools;
use std::io::{BufRead, stdin};

fn number(ds: Vec<u64>) -> u64 {
    if ds.is_empty() {
        0
    } else {
        let mut ans = 0;
        let mut mul = 1;

        for d in ds.into_iter().rev() {
            ans += d * mul;
            mul *= 10;
        }

        ans
    }
}

fn max_seq_of_len_k(xs: Vec<u64>, k: uzize) -> Vec<u64> {
    let mut result: Vec<u64> = vec![];
    let mut i0: usize = 0;

    while result.len() < k {
        let i = xs[..k - result.len()]
            .iter()
            .enumerate()
            .max_by_key(|(_, x)| x)
            .unwrap()
            .0;
        result.push(xs[i]);
        i0 = i + 1;
    }

    result
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();

    let grid: Vec<Vec<u64>> = lines
        .into_iter()
        .map(|s| s.bytes().map(|x| (x - b'0') as u64).collect())
        .collect();

    let n = grid[0].len();

    let mut result = 0;
    for row in grid {
        let mut cur = 0;

        let i: usize = row[..n - 12]
            .iter()
            .enumerate()
            .max_by_key(|&(j, _)| j)
            .unwrap()
            .0;

        for xs in row[i..].iter().cloned().combinations(12) {
            cur = cur.max(number(xs));
        }

        result += cur;
    }
    println!("{result}");
}
