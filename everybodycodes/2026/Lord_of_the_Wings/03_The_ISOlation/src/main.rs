use itertools::Itertools;
use std::{
    collections::HashMap,
    io::{BufRead, stdin},
    iter::successors,
};

fn digits_reversed(x: u64) -> Vec<u64> {
    successors(Some(x), |&n| (n > 9).then_some(n / 10))
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

fn vote_value(standard: u64, vote: u64) -> u64 {
    let vote_digits = digits(vote);
    let n = vote_digits.len();

    vote_digits
        .into_iter()
        .rev()
        .zip(
            grow_by_repeating(digits(standard), n)
                .into_iter()
                .rev()
                .enumerate(),
        )
        .map(|(k, (exp, base))| k * base.pow(exp as u32))
        .sum()
}

fn min_votes_by_value(standard: u64) -> HashMap<u64, u64> {
    (0..1_000_000).fold(HashMap::new(), |mut agg, vote| {
        agg.entry(vote_value(standard, vote)).or_insert(vote);
        agg
    })
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let lines_decoded: Vec<_> = lines.into_iter().map(|line| decode_line(&line)).collect();

    let min_votes_by_value_by_standard: HashMap<u64, HashMap<u64, u64>> = lines_decoded
        .iter()
        .map(|(standard, _)| *standard)
        .unique()
        .fold(HashMap::new(), |mut agg, standard| {
            agg.entry(standard).or_insert(min_votes_by_value(standard));
            agg
        });

    let vote_values: Vec<_> = lines_decoded
        .into_iter()
        .map(|(standard, vote)| {
            let vv = vote_value(standard, vote);

            let min_vote = *min_votes_by_value_by_standard
                .get(&standard)
                .and_then(|mvbv| mvbv.get(&vv))
                .unwrap();

            if min_vote == vote { vv } else { 0 }
        })
        .collect();

    println!("{}", vote_values.into_iter().sum::<u64>());
}
