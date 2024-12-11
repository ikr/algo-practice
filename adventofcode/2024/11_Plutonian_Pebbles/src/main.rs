use std::{
    collections::HashMap,
    io::{self, BufRead},
};

use itertools::Itertools;

fn evolve(x: u64) -> Vec<u64> {
    if x == 0 {
        vec![1]
    } else {
        let ds: Vec<u8> = x.to_string().bytes().collect();
        if ds.len() % 2 == 0 {
            let a: String = String::from_utf8(ds[0..ds.len() / 2].to_vec()).unwrap();
            let b: String = String::from_utf8(ds[ds.len() / 2..].to_vec()).unwrap();
            [a, b].iter().map(|x| x.parse().unwrap()).collect()
        } else {
            vec![x * 2024]
        }
    }
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().to_string())
        .collect();

    let xs: Vec<u64> = lines[0]
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let mut fqs: HashMap<u64, usize> = xs.into_iter().counts();

    for _ in 0..75 {
        let mut new_fqs: HashMap<u64, usize> = HashMap::new();
        for (x, f) in fqs.iter() {
            for y in evolve(*x) {
                *new_fqs.entry(y).or_insert(0) += f;
            }
        }
        fqs = new_fqs;
    }

    println!("{}", fqs.values().sum::<usize>());
}
