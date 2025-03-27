use std::io::{BufRead, stdin};

fn all_digits() -> Vec<char> {
    let mut result: Vec<char> = ('0'..='9').collect();
    result.extend('A'..='Z');
    result.extend('a'..='z');
    result
}

fn decode_value(s: &str, radix: usize) -> usize {
    let alphabet = all_digits();
    let digit_value = |c: char| alphabet.iter().position(|&x| x == c).unwrap();
    let mut result = 0;
    let mut m: usize = 1;

    for c in s.chars().rev() {
        result += m * digit_value(c);
        m *= radix;
    }

    result
}

fn main() {
    let lines: Vec<(String, usize)> = stdin()
        .lock()
        .lines()
        .map(|line| {
            let s = line.unwrap();
            let ps: Vec<_> = s.split_whitespace().collect();
            (ps[0].to_string(), ps[1].parse().unwrap())
        })
        .collect();

    let result: usize = lines
        .into_iter()
        .map(|(s, b)| decode_value(&s, b))
        .max()
        .unwrap();
    println!("{}", result);
}
