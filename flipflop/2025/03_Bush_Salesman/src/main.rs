use itertools::Itertools;
use std::io::{BufRead, stdin};

fn decode_line(s: &str) -> (u8, u8, u8) {
    s.split(',')
        .map(|sub| sub.parse().unwrap())
        .collect_tuple()
        .unwrap()
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();

    let fqs: Vec<_> = lines
        .into_iter()
        .map(|s| decode_line(&s))
        .counts()
        .into_iter()
        .collect();

    let result = fqs.into_iter().max_by_key(|(_, f)| f).unwrap().0;
}
