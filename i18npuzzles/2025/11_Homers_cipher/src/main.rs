use std::io::{self, BufRead};

fn remove_punctuation(s: String) -> String {
    s.chars()
        .filter(|c| c.is_alphabetic() || *c == ' ')
        .collect()
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| remove_punctuation(line.expect("Next stdin line available")))
        .collect();

    eprintln!("{:?}", lines)
}
