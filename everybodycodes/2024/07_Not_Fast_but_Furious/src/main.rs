use std::io::{self, BufRead};

fn parse_line(s: &str) -> (String, Vec<i32>) {
    let parts: Vec<&str> = s.split(":").collect();
    let lhs = parts[0].to_string();
    let rhs = parts[1]
        .split(",")
        .map(|s| match s {
            "-" => -1,
            "=" => 0,
            "+" => 1,
            _ => panic!("Unknown op {}", s),
        })
        .collect();
    (lhs, rhs)
}

fn total_essence_gathered(segments: usize, initial_essence: i32, xs: &[i32]) -> i32 {
    let mut cur = initial_essence;
    let mut result = 0;
    let m = xs.len();

    for i in 0..segments {
        cur += xs[i % m];
        result += cur;
    }

    result
}

fn main() {
    let mut lines = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_line(&line.unwrap()))
        .collect::<Vec<_>>();

    lines.sort_by_key(|(_, xs)| -total_essence_gathered(10, 10, &xs));
    let result = lines
        .into_iter()
        .map(|(s, _)| s)
        .collect::<Vec<_>>()
        .join("");
    println!("{}", result);
}
