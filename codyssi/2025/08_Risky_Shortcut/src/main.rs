use std::io::{self, BufRead};

fn alpha_count(s: &str) -> usize {
    s.chars().filter(|c| c.is_alphabetic()).count()
}

fn main() {
    let lines: Vec<String> = io::stdin().lock().lines().map(|s| s.unwrap()).collect();
    let result: usize = lines.into_iter().map(|s| alpha_count(&s)).sum();
    println!("{}", result);
}
