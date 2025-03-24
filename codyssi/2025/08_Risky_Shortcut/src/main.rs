use std::io::{self, BufRead};

fn first_reduction_index(s: &str) -> Option<usize> {
    let ps: Vec<(char, char)> = s
        .chars()
        .collect::<Vec<_>>()
        .windows(2)
        .map(|ab| (ab[0], ab[1]))
        .collect();

    ps.into_iter().position(|(a, b)| {
        (a.is_alphabetic() && b.is_ascii_digit()) || (a.is_ascii_digit() && b.is_alphabetic())
    })
}

fn reduce_all(s: &str) -> String {
    let mut result = s.to_string();
    while let Some(i) = first_reduction_index(&result) {
        result = result[..i].to_string() + &result[i + 2..];
    }
    result
}

fn main() {
    let lines: Vec<String> = io::stdin().lock().lines().map(|s| s.unwrap()).collect();
    let result: usize = lines.into_iter().map(|s| reduce_all(&s).len()).sum();
    println!("{}", result);
}
