use std::io::{BufRead, stdin};

use itertools::Itertools;

fn digits(s: &str) -> Vec<u32> {
    s.bytes().map(|x| (x - b'0') as u32).collect()
}

fn decode_line(line: &str) -> (Vec<u32>, Vec<u32>) {
    let (a, b) = line.split(' ').collect_tuple().unwrap();
    (digits(a.strip_prefix("ISO-").unwrap()), digits(b))
}

fn vote_value(standard: Vec<u32>, vote: Vec<u32>) -> u32 {
    standard
        .into_iter()
        .rev()
        .enumerate()
        .zip(vote.into_iter().rev())
        .map(|((exp, base), k)| k * base.pow(exp as u32))
        .sum()
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let line_decoded: Vec<_> = lines.into_iter().map(|line| decode_line(&line)).collect();

    let vote_values: Vec<_> = line_decoded
        .into_iter()
        .map(|(a, b)| vote_value(a, b))
        .collect();

    println!("{}", vote_values.into_iter().sum::<u32>());
}
