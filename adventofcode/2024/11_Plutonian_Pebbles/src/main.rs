use itertools::Itertools;
use std::collections::HashMap;

fn evolve(x: u64) -> Vec<u64> {
    if x == 0 {
        vec![1]
    } else {
        let ds = x.to_string();
        let n = ds.len();
        if n % 2 == 0 {
            [&ds[0..n / 2], &ds[n / 2..]]
                .into_iter()
                .map(|x| x.parse().unwrap())
                .collect()
        } else {
            vec![x * 2024]
        }
    }
}

fn main() {
    let xs: Vec<u64> = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let mut fqs: HashMap<u64, usize> = xs.into_iter().counts();

    for _ in 0..75 {
        fqs = fqs
            .iter()
            .flat_map(|(&x, &f)| evolve(x).into_iter().map(|y| (y, f)).collect::<Vec<_>>())
            .fold(HashMap::new(), |mut acc, (x, f)| {
                acc.entry(x).and_modify(|ff| *ff += f).or_insert(f);
                acc
            });
    }

    println!("{}", fqs.values().sum::<usize>());
}
