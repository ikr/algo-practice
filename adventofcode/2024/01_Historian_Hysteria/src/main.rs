use std::{
    collections::HashMap,
    io::{self, BufRead},
};

fn main() {
    let xys: Vec<(u32, u32)> = io::stdin()
        .lock()
        .lines()
        .map(|line| {
            let parts: Vec<u32> = line
                .unwrap()
                .split_whitespace()
                .map(|x| x.parse().unwrap())
                .collect();
            (parts[0], parts[1])
        })
        .collect();

    let y_freqs: HashMap<u32, u32> =
        xys.iter()
            .map(|(_, y)| *y)
            .fold(HashMap::new(), |mut acc, y| {
                acc.entry(y).and_modify(|f| *f += 1).or_insert(1);
                acc
            });

    let result: u32 = xys
        .into_iter()
        .map(|(x, _)| x * *y_freqs.get(&x).unwrap_or(&0))
        .sum();

    println!("{}", result);
}
