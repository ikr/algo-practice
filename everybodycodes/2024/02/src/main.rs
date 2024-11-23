use std::{
    collections::HashSet,
    io::{self, BufRead},
};

fn reversed(s: &[u8]) -> Vec<u8> {
    let mut xs = s.to_vec();
    xs.reverse();
    xs
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap())
        .collect();

    let words: Vec<String> = lines[0]
        .strip_prefix("WORDS:")
        .unwrap()
        .split(',')
        .map(|s| s.trim().to_string())
        .collect();

    let grid: Vec<Vec<u8>> = lines[2..]
        .iter()
        .map(|line| line.as_bytes().iter().cloned().collect())
        .collect();

    eprintln!("{:?}", grid);
}
