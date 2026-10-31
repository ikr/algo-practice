use std::io::{BufRead, stdin};

use itertools::Itertools;

fn digits(s: &str) -> Vec<u64> {
    s.bytes().map(|x| (x - b'0') as u64).collect()
}

fn decode_line(line: &str) -> (Vec<u64>, Vec<u64>) {
    let (a, b) = line.split(' ').collect_tuple().unwrap();
    (digits(a.strip_prefix("ISO-").unwrap()), digits(b))
}

fn grow_by_repeating<T: Copy>(s: Vec<T>, target_length: usize) -> Vec<T> {
    if s.is_empty() || s.len() >= target_length {
        s
    } else {
        let q = target_length / s.len();
        let r = target_length % s.len();
        s.iter().tail(r).copied().chain(s.repeat(q)).collect()
    }
}

fn vote_value(standard: Vec<u64>, vote: Vec<u64>) -> u64 {
    let n = vote.len();

    vote.into_iter()
        .rev()
        .zip(grow_by_repeating(standard, n).into_iter().rev().enumerate())
        .map(|(k, (exp, base))| k * base.pow(exp as u32))
        .sum()
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let line_decoded: Vec<_> = lines.into_iter().map(|line| decode_line(&line)).collect();

    let vote_values: Vec<_> = line_decoded
        .into_iter()
        .map(|(a, b)| vote_value(a, b))
        .collect();

    println!("{}", vote_values.into_iter().sum::<u64>());
}
