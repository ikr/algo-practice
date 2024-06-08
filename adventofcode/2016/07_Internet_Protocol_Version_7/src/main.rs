use regex::Regex;
use std::io::{self, BufRead};

fn extract_parts(src: &str) -> (String, String, String) {
    let re = Regex::new(r"^([a-z]+)\[([a-z]+)\]([a-z]+)$").unwrap();
    let caps = re.captures(src).unwrap();
    (
        caps[1].to_string(),
        caps[2].to_string(),
        caps[3].to_string(),
    )
}

fn has_an_abba(xs: &str) -> bool {
    xs.chars().collect::<Vec<_>>().windows(4).any(|abcd| {
        let [a, b, c, d] = abcd else {
            panic!("{:?} isn't a quad", abcd)
        };
        a != b && b == c && a == d
    })
}

fn main() {
    let line_parts: Vec<(String, String, String)> = io::stdin()
        .lock()
        .lines()
        .map(|line| extract_parts(&line.unwrap()))
        .collect();

    eprintln!("{:?}", line_parts);
}
