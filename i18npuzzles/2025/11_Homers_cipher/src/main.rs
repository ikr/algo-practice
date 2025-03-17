use std::io::{self, BufRead};

const NEEDLES: [&str; 5] = ["Οδυσσευσ", "Οδυσσεωσ", "Οδυσσει", "Οδυσσεα", "Οδυσσευ"];
const AL_HI: &str = "ΑΒΓΔΕΖΗΘΙΚΛΜΝΞΟΠΡΣΤΥΦΧΨΩ";
const AL_LO: &str = "αβγδεζηθικλμνξοπρστυφχψω";

fn remove_punctuation(s: String) -> String {
    s.chars()
        .filter(|c| c.is_alphabetic() || *c == ' ')
        .collect()
}

fn normalize_sigma(s: String) -> String {
    s.chars().map(|c| if c == 'ς' { 'σ' } else { c }).collect()
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.expect("Next stdin line available"))
        .map(remove_punctuation)
        .map(normalize_sigma)
        .collect();

    eprintln!("{:?}", lines)
}
