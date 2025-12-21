use regex::Regex;
use std::io::{BufRead, stdin};

fn relevant_tokens_count(s: &str) -> usize {
    Regex::new(r"ba|na|ne").unwrap().find_iter(s).count()
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();

    let tcs: Vec<usize> = lines
        .into_iter()
        .filter_map(|s| {
            let c = relevant_tokens_count(&s);
            c.is_multiple_of(2).then_some(c)
        })
        .collect();

    let result: usize = tcs.into_iter().sum();
    println!("{result}");
}
