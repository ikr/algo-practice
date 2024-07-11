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

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap())
        .collect();

    let result = lines
        .into_iter()
        .fold(0, |acc, s| acc + s.len() - decode(&s).len());
    println!("{}", result);
}
