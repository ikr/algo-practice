use std::{
    collections::{HashMap, HashSet, VecDeque},
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

fn toposort(before: &HashSet<(usize, usize)>, xs: &[usize]) -> Vec<usize> {
    let after = |u0: usize| -> Vec<usize> {
        before
            .iter()
            .filter(|(u, v)| *u == u0 && xs.contains(v))
            .map(|(_, v)| *v)
            .collect()
    };

    let mut indeg: HashMap<usize, usize> = before
        .iter()
        .filter(|(u, v)| xs.contains(u) && xs.contains(v))
        .fold(
            xs.iter().map(|x| (*x, 0usize)).collect(),
            |mut acc, (_, v)| {
                acc.entry(*v).and_modify(|x| *x += 1);
                acc
            },
        );

    let mut q: VecDeque<usize> = xs
        .iter()
        .filter(|x| *indeg.get(x).unwrap() == 0)
        .cloned()
        .collect();

    let mut result = vec![];
    while let Some(u) = q.pop_front() {
        result.push(u);
        for v in after(u) {
            indeg.entry(v).and_modify(|x| *x -= 1);
            if *indeg.get(&v).unwrap() == 0 {
                q.push_back(v);
            }
        }
    }
    result
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
