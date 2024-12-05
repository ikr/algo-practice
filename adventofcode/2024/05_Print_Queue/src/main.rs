use std::{
    cmp::Ordering,
    collections::HashSet,
    io::{self, BufRead},
};

use itertools::Itertools;

fn is_ok(before: &HashSet<(usize, usize)>, queue: &[usize]) -> bool {
    queue
        .iter()
        .combinations(2)
        .all(|ab| !before.contains(&(*ab[1], *ab[0])))
}

fn parse_rule(s: &str) -> (usize, usize) {
    let parts: Vec<usize> = s.split('|').map(|x| x.parse().unwrap()).collect();
    (parts[0], parts[1])
}

fn parse_queue(s: &str) -> Vec<usize> {
    s.split(',').map(|x| x.parse().unwrap()).collect()
}

fn toposort(before: &HashSet<(usize, usize)>, xs0: &[usize]) -> Vec<usize> {
    let mut xs = xs0.to_vec();
    xs.sort_by(|&a, &b| {
        if before.contains(&(a, b)) {
            Ordering::Less
        } else if before.contains(&(b, a)) {
            Ordering::Greater
        } else {
            Ordering::Equal
        }
    });
    xs
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
        .map(|xs| toposort(&before, &xs)[xs.len() / 2])
        .sum();
    println!("{}", result);
}
