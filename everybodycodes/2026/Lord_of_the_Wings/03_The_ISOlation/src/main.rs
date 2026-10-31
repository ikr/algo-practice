use itertools::Itertools;
use std::{
    io::{BufRead, stdin},
    iter::successors,
};

fn digits_reversed(x: u64) -> Vec<u64> {
    successors(Some(x), |&n| (n >= 10).then_some(n / 10))
        .map(|n| n % 10)
        .collect()
}

fn digits(x: u64) -> Vec<u64> {
    let mut result = digits_reversed(x);
    result.reverse();
    result
}

fn decode_line(line: &str) -> (u64, u64) {
    let i_dash = line.bytes().position(|x| x == b'-').unwrap();
    let (a, b) = line[i_dash + 1..].split(' ').collect_tuple().unwrap();
    (a.parse().unwrap(), b.parse().unwrap())
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

fn number(digits: &[u64]) -> u64 {
    digits
        .iter()
        .rev()
        .fold((0, 1), |(s, m), d| (s + m * d, m * 10))
        .0
}

//fn min_votes_by_value()

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let line_decoded: Vec<_> = lines.into_iter().map(|line| decode_line(&line)).collect();

    let vote_values: Vec<_> = line_decoded
        .into_iter()
        .map(|(a, b)| vote_value(digits(a), digits(b)))
        .collect();

    eprintln!("{vote_values:?}");
    println!("{}", vote_values.into_iter().sum::<u64>());
}
