use std::io::{BufRead, stdin};

fn all_digits() -> Vec<char> {
    let mut result: Vec<char> = ('0'..='9').collect();
    result.extend('A'..='Z');
    result.extend('a'..='z');
    result.extend(['!', '@', '#', '$', '%', '^']);
    result.extend(vec!['?'; 9000]);
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

fn encode_value(mut v: usize, radix: usize) -> String {
    if v == 0 {
        return "0".to_string();
    }

    let alphabet = all_digits();
    let mut ds: Vec<char> = vec![];

    while v != 0 {
        ds.push(alphabet[v % radix]);
        v /= radix;
    }

    ds.reverse();
    ds.into_iter().collect()
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

    let x0: usize = lines.into_iter().map(|(s, b)| decode_value(&s, b)).sum();

    for radix in 2..9000 {
        let s = encode_value(x0, radix);
        if s.len() == 4 {
            println!("{}", radix);
            break;
        }
    }
}
