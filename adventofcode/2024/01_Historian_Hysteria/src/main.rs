use std::{
    collections::HashMap,
    io::{self, BufRead},
};

fn main() {
    let grid: Vec<(u32, u32)> = io::stdin()
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

    let mut xs: Vec<u32> = grid.iter().map(|(x, _)| *x).collect();
    xs.sort();

    let ys: HashMap<u32, u32> = grid
        .iter()
        .map(|(_, y)| *y)
        .fold(HashMap::new(), |mut acc, y| {
            acc.entry(y).and_modify(|f| *f += 1).or_insert(1);
            acc
        });

    let result: u64 = xs
        .into_iter()
        .map(|x| (x as u64) * (*ys.get(&x).unwrap_or(&0) as u64))
        .sum();

    println!("{}", result);
}
