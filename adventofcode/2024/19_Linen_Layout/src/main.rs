use std::io::{self, BufRead};

fn parse_patterns(s: &str) -> Vec<Vec<u8>> {
    s.split(", ").map(|t| t.bytes().collect()).collect()
}

fn stringify(xs: &[u8]) -> String {
    String::from_utf8(xs.to_vec()).unwrap()
}

fn is_possible(patterns: &[Vec<u8>], design: &[u8]) -> bool {
    if design.is_empty() || patterns.contains(&design.to_vec()) {
        true
    } else {
        patterns.iter().any(|pattern| {
            let m = pattern.len();
            m <= design.len() && design[0..m] == *pattern && is_possible(patterns, &design[m..])
        })
    }
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().to_string())
        .collect();

    let patterns = parse_patterns(&lines[0]);

    let isep = lines.iter().position(|line| line.is_empty()).unwrap();

    let designs: Vec<Vec<u8>> = lines[isep + 1..]
        .iter()
        .map(|line| line.bytes().collect())
        .collect();

    let result = designs
        .iter()
        .filter(|design| is_possible(&patterns, design))
        .count();
    println!("{}", result);
}
