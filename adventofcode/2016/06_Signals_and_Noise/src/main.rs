use std::{
    collections::HashMap,
    io::{self, BufRead},
};

fn transpose<T>(grid: Vec<Vec<T>>) -> Vec<Vec<T>> {
    assert!(!grid.is_empty());
    let h = grid[0].len();
    let mut iters: Vec<_> = grid.into_iter().map(|n| n.into_iter()).collect();
    (0..h)
        .map(|_| {
            iters
                .iter_mut()
                .map(|n| n.next().unwrap())
                .collect::<Vec<T>>()
        })
        .collect()
}

fn frequencies(xs: &[char]) -> HashMap<char, u16> {
    xs.iter().fold(HashMap::new(), |mut acc, c| {
        acc.entry(*c).and_modify(|f| *f += 1).or_insert(1);
        acc
    })
}

fn most_frequent_one(xs: &[char]) -> char {
    frequencies(xs)
        .into_iter()
        .max_by(|a, b| (a.1, a.0).cmp(&(b.1, b.0)))
        .unwrap()
        .0
}

fn main() {
    let lines: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let result: String = transpose(lines)
        .into_iter()
        .map(|line| most_frequent_one(&line))
        .collect();
    println!("{}", result);
}
