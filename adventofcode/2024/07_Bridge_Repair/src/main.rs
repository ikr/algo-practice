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

fn concat(x: u64, y: u64) -> u64 {
    (x.to_string() + &y.to_string()).parse().unwrap()
}

fn evaluate(xs: &[u64], mul_indices: &[usize], concat_indices: &[usize]) -> u64 {
    xs.iter().enumerate().skip(1).fold(xs[0], |acc, (i, &x)| {
        if mul_indices.contains(&(i - 1)) {
            acc * x
        } else if concat_indices.contains(&(i - 1)) {
            concat(acc, x)
        } else {
            acc + x
        }
    })
}

fn without(ii: &[usize], jj: &[usize]) -> Vec<usize> {
    ii.iter().filter(|i| !jj.contains(i)).cloned().collect()
}

fn is_satisfiable(lhs: u64, xs: &[u64]) -> bool {
    let n = xs.len();
    for mul_indices in (0..n - 1).powerset() {
        let ri = without(&(0..n - 1).collect::<Vec<_>>(), &mul_indices);
        for concat_indices in ri.into_iter().powerset() {
            if evaluate(xs, &mul_indices, &concat_indices) == lhs {
                return true;
            }
        }
    }
    false
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
