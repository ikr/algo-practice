use std::{
    collections::{HashMap, HashSet},
    io::{self, BufRead},
};

const M: u64 = 16777216;

fn evolve(mut x: u64) -> u64 {
    let a = x * 64;
    x = (x ^ a) % M;
    let c = x / 32;
    x = (x ^ c) % M;
    let e = x * 2048;
    x = (x ^ e) % M;
    x
}

fn evolve_2000(x: u64) -> Vec<u64> {
    let mut result = vec![x];
    for _ in 0..2000 {
        result.push(evolve(*result.last().unwrap()));
    }
    result
}

fn banana_windows(xs: &[u64]) -> Vec<(i8, [i8; 4])> {
    let deltas: Vec<i8> = xs
        .windows(2)
        .map(|ab| {
            let a = (ab[0] % 10) as i8;
            let b = (ab[1] % 10) as i8;
            b - a
        })
        .collect();

    let xds: Vec<(i8, i8)> = xs[1..]
        .iter()
        .zip(deltas.into_iter())
        .map(|(&x, d)| ((x % 10) as i8, d))
        .collect();

    xds.windows(4)
        .map(|pquad| {
            let last_x = pquad.last().unwrap().0;
            let ds = pquad.iter().map(|(_, d)| *d).collect::<Vec<_>>();
            (last_x, ds.try_into().unwrap())
        })
        .collect()
}

fn max_banana_by_window(bws: &[(i8, [i8; 4])]) -> HashMap<[i8; 4], i8> {
    bws.iter().fold(HashMap::new(), |mut acc, (b, w)| {
        acc.entry(*w)
            .and_modify(|x| {
                *x = if b > x { *b } else { *x };
            })
            .or_insert(*b);
        acc
    })
}

fn main() {
    let xs: Vec<u64> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().parse().unwrap())
        .collect();

    let mbbws = xs
        .into_iter()
        .map(evolve_2000)
        .map(|xs| max_banana_by_window(&banana_windows(&xs)))
        .collect::<Vec<_>>();

    let mut all_windows: HashSet<[i8; 4]> = HashSet::new();
    for mbbw in mbbws.iter() {
        for (k, _) in mbbw {
            all_windows.insert(*k);
        }
    }

    let mut result: u16 = 0;
    for w in all_windows {
        let mut candidate: u16 = 0;

        for mbbw in mbbws.iter() {
            candidate += *mbbw.get(&w).unwrap_or(&0) as u16;
        }

        result = result.max(candidate);
    }
    println!("{}", result);
}
