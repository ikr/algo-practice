use itertools::Itertools;
use std::io::{BufRead, stdin};

const LO: usize = 7;
const HI: usize = 11;

fn decode_rule(s: &str) -> Vec<(char, char)> {
    let first = |x: &str| -> char { x.chars().next().unwrap() };
    let parts: Vec<_> = s.split(" > ").collect();
    let a: char = first(parts[0]);
    parts[1].split(',').map(|x| (a, first(x))).collect()
}

fn is_valid_word(rule_pairs: &[(char, char)], word: &[char]) -> bool {
    word.windows(2)
        .all(|xy| rule_pairs.contains(&(xy[0], xy[1])))
}

fn words_from(rule_pairs: &[(char, char)], prefix: Vec<char>) -> Vec<String> {
    if prefix.len() == HI {
        return vec![prefix.into_iter().collect()];
    }

    let base: Vec<String> = if prefix.len() < LO {
        vec![]
    } else {
        vec![prefix.iter().cloned().collect()]
    };
    let t: char = *prefix.last().unwrap();

    rule_pairs
        .iter()
        .filter_map(|&(x, y)| {
            if x == t {
                let mut new_prefix = prefix.clone();
                new_prefix.push(y);
                Some(words_from(rule_pairs, new_prefix))
            } else {
                None
            }
        })
        .flatten()
        .chain(base)
        .collect()
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let names: Vec<String> = lines[0].split(',').map(|x| x.to_string()).collect();
    let rule_pairs: Vec<(char, char)> = lines[2..].iter().flat_map(|x| decode_rule(x)).collect();

    let words: Vec<String> = names
        .into_iter()
        .filter_map(|s| {
            let xs: Vec<_> = s.chars().collect();
            if is_valid_word(&rule_pairs, &xs) {
                Some(words_from(&rule_pairs, xs))
            } else {
                None
            }
        })
        .flatten()
        .sorted()
        .dedup()
        .collect();

    println!("{}", words.len());
}
