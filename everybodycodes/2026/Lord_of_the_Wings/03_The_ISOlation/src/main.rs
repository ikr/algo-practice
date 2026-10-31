use std::io::{BufRead, stdin};

fn decode_digits_from_line(line: &str) -> Vec<u32> {
    line.split(' ')
        .last()
        .unwrap()
        .bytes()
        .map(|x| (x - b'0') as u32)
        .collect()
}

fn vote_value(digits: Vec<u32>) -> u32 {
    let base = digits[0];

    digits
        .into_iter()
        .skip(1)
        .rev()
        .fold((0, 1), |(s, m), d| (s + m * d, m * base))
        .0
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();

    let line_digits: Vec<_> = lines
        .into_iter()
        .map(|line| decode_digits_from_line(&line))
        .collect();

    let vote_values: Vec<_> = line_digits.into_iter().map(vote_value).collect();
    eprintln!("{vote_values:?}");
}
