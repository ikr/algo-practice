use std::io::{BufRead, stdin};

fn decode_range(s: &str) -> (u64, u64) {
    let parts = s.split('-').collect::<Vec<_>>();
    (parts[0].parse().unwrap(), parts[1].parse().unwrap())
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let isep = lines.iter().position(|s| s.is_empty()).unwrap();
    let ranges: Vec<(u64, u64)> = lines[..isep].iter().map(|s| decode_range(s)).collect();

    let ids: Vec<u64> = lines[isep + 1..]
        .iter()
        .map(|s| s.parse().unwrap())
        .collect();

    let result = ids
        .into_iter()
        .filter(|&id| ranges.iter().any(|&(a, b)| a <= id && id <= b))
        .count();
    println!("{result}");
}
