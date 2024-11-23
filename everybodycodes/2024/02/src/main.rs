use std::io::{self, BufRead};

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap())
        .collect();

    let words: Vec<String> = lines[0]
        .strip_prefix("WORDS:")
        .unwrap()
        .split(',')
        .map(|s| s.trim().to_string())
        .collect();

    let haystack = &lines[2];

    let result: usize = words
        .iter()
        .map(|w| haystack.match_indices(w).count())
        .sum();

    println!("{}", result);
}
