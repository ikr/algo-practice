use std::io::{self, BufRead};

fn decode(src: &str) -> Vec<u8> {
    let a: &str = src
        .strip_prefix('"')
        .and_then(|x| x.strip_suffix('"'))
        .unwrap();

    todo!()
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
