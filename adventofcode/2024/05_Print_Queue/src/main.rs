use std::{
    collections::HashSet,
    io::{self, BufRead},
};

use itertools::Itertools;

fn is_ok(rules: &HashSet<(usize, usize)>, queue: &[usize]) -> bool {
    queue.iter().combinations(2).all(|ab| {
        let a = ab[0];
        let b = ab[1];
        !rules.contains(&(*b, *a))
    })
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

    let mut rules: Vec<(usize, usize)> = vec![];
    let mut queues: Vec<Vec<usize>> = vec![];

    for (i, line) in lines.iter().enumerate() {
        if line == "" {
            lines[i + 1..]
                .iter()
                .for_each(|line| queues.push(parse_queue(&line)));

            break;
        }
        rules.push(parse_rule(&line));
    }

    eprintln!("{:?}", rules);
    eprintln!("{:?}", queues);

    let before: HashSet<_> = rules.into_iter().collect();
    let mut incorrect: Vec<_> = queues
        .iter()
        .filter(|queue| !is_ok(&before, queue))
        .collect();

    let mut result: usize = 0;
    for xs0 in incorrect {
        let n = xs0.len();
        let mut xs = xs0.clone();
        for i in 0..n - 1 {
            for j in i..n {
                if before.contains(&(xs[j], xs[i])) {
                    xs.swap(i, j);
                }
            }
        }
        result += xs[n / 2];
    }
    println!("{}", result);
}
