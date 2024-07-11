use regex::Regex;
use std::io::{self, BufRead};

fn decode(src: &str) -> String {
    let a: String = src
        .strip_prefix('"')
        .and_then(|x| x.strip_suffix('"'))
        .unwrap()
        .replace("\\\\x", "\\\\X")
        .replace("\\\\\"", "\\\\Q")
        .replace("\\\\", "\\")
        .replace("\\\"", "\"")
        .to_owned();

    let re = Regex::new(r"(\\x)([a-z0-9][a-z0-9])").unwrap();
    re.replace_all(&a, "Z").into_owned()
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap())
        .collect();
    for line in lines.iter() {
        eprintln!("{} → {}", line, decode(line));
    }

    let result = lines
        .into_iter()
        .fold(0, |acc, s| acc + s.len() - decode(&s).len());
    println!("{}", result);
}
