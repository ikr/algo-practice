use std::io::{self, BufRead};

use itertools::Itertools;

fn parse_line(s: &str) -> (u64, Vec<u64>) {
    let parts = s.split(": ").map(|x| x.to_string()).collect::<Vec<_>>();
    let rhs = parts[1]
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect::<Vec<_>>();
    (parts[0].parse().unwrap(), rhs)
}

fn evaluate(xs: &[u64], mul_indices: &[usize]) -> u64 {
    xs.iter().enumerate().skip(1).fold(xs[0], |acc, (i, &x)| {
        if mul_indices.contains(&(i - 1)) {
            acc * x
        } else {
            acc + x
        }
    })
}

fn is_satisfiable(lhs: u64, xs: &[u64]) -> bool {
    (0..xs.len() - 1)
        .powerset()
        .any(|ii| evaluate(xs, &ii) == lhs)
}

fn main() {
    let lines: Vec<_> = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_line(&line.unwrap()))
        .collect();

    let result: u64 = lines
        .into_iter()
        .filter(|(lhs, xs)| is_satisfiable(*lhs, xs))
        .map(|(lhs, _)| lhs)
        .sum();
    println!("{}", result);
}
