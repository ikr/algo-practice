use std::io::{self, BufRead};

fn decode(src: &str) -> Vec<u8> {
    let xs: &[u8] = src
        .strip_prefix('"')
        .and_then(|x| x.strip_suffix('"'))
        .unwrap()
        .as_bytes();

    let mut result: Vec<u8> = vec![];
    let mut i: usize = 0;

    while i < xs.len() {
        if xs[i] == b'\\' {
            assert!(i + 1 < xs.len());
            if xs[i + 1] == b'x' {
                let hex = String::from_utf8(xs[i + 2..i + 4].to_vec()).unwrap();
                let b: u8 = u8::from_str_radix(&hex, 16).unwrap();
                result.push(b);
                i += 4;
            } else {
                result.push(xs[i + 1]);
                i += 2;
            }
        } else {
            result.push(xs[i]);
            i += 1;
        }
    }

    result
}

fn encoded_length(xs: &[u8]) -> usize {
    let bss = xs.iter().filter(|x| **x == b'\\').count();
    let qs = xs.iter().filter(|x| **x == b'"').count();
    xs.len() + bss + qs + 6
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap())
        .collect();

    let result1 = lines
        .iter()
        .fold(0, |acc, s| acc + s.len() - decode(s).len());
    println!("{}", result1);

    let result2 = lines.into_iter().fold(0, |acc, s| {
        acc + encoded_length(
            s.strip_prefix('"')
                .and_then(|x| x.strip_suffix('"'))
                .unwrap()
                .as_bytes(),
        ) - s.len()
    });
    println!("{}", result2);
}
