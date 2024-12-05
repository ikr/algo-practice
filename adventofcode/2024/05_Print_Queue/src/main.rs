use std::{
    collections::HashSet,
    io::{self, BufRead},
};

use itertools::Itertools;

fn is_ok(rules: &HashSet<(usize, usize)>, queue: &[usize]) -> bool {
    queue
        .iter()
        .combinations(2)
        .all(|ab| !rules.contains(&(*ab[1], *ab[0])))
}

fn parse_rule(s: &str) -> (usize, usize) {
    let parts: Vec<usize> = s.split('|').map(|x| x.parse().unwrap()).collect();
    (parts[0], parts[1])
}

fn parse_queue(s: &str) -> Vec<usize> {
    s.split(',').map(|x| x.parse().unwrap()).collect()
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().to_string())
        .collect();

    let isep = lines.iter().position(|line| line.is_empty()).unwrap();

    let before: HashSet<(usize, usize)> =
        lines[0..isep].iter().map(|line| parse_rule(line)).collect();

    let queues: Vec<Vec<usize>> = lines[isep + 1..]
        .iter()
        .map(|line| parse_queue(line))
        .collect();

    let result: usize = queues
        .into_iter()
        .filter(|queue| !is_ok(&before, queue))
        .map(|xs0| {
            let n = xs0.len();
            let mut xs = xs0.clone();
            for ij in (0..n).combinations(2) {
                let [i, j] = ij[..] else { panic!() };
                if before.contains(&(xs[j], xs[i])) {
                    xs.swap(i, j);
                }
            }
            xs[n / 2]
        })
        .sum();
    println!("{}", result);
}
