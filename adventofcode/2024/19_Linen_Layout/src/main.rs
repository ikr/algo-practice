use std::io::{self, BufRead};

fn parse_patterns(s: &str) -> Vec<Vec<u8>> {
    s.split(", ").map(|t| t.bytes().collect()).collect()
}

fn num_ways(patterns: &[Vec<u8>], design: &[u8]) -> u64 {
    let n = design.len();
    let mut dp: Vec<u64> = vec![0; n];
    for i in 0..n {
        for p in patterns {
            let m = p.len();
            if i + m <= n && (i == 0 || dp[i - 1] != 0) && design[i..i + m] == *p {
                dp[i + m - 1] += if i == 0 { 1 } else { dp[i - 1] };
            }
        }
    }
    dp[n - 1]
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

    let result: u64 = designs
        .iter()
        .map(|design| num_ways(&patterns, design))
        .sum();
    println!("{}", result);
}
