use std::{
    collections::HashMap,
    io::{self, BufRead},
};

use itertools::Itertools;

fn main() {
    let xys: Vec<(usize, usize)> = io::stdin()
        .lock()
        .lines()
        .map(|line| {
            let parts: Vec<usize> = line
                .unwrap()
                .split_whitespace()
                .map(|x| x.parse().unwrap())
                .collect();
            (parts[0], parts[1])
        })
        .collect();

    let y_freqs: HashMap<usize, usize> = xys.iter().map(|(_, y)| *y).counts();

    let result: usize = xys
        .into_iter()
        .map(|(x, _)| x * *y_freqs.get(&x).unwrap_or(&0))
        .sum();

    println!("{}", result);
}
