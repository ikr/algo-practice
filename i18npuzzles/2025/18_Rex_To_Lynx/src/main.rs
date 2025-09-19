use std::io::{BufRead, stdin};

const RLI: char = '\u{2067}';
const LRI: char = '\u{2066}';
const PDI: char = '\u{2069}';

fn remove_bidi_markers(s: &str) -> String {
    s.chars().filter(|c| ![RLI, LRI, PDI].contains(c)).collect()
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    eprintln!("{:?}", lines);

    let naive_lines: Vec<String> = lines.iter().map(|s| remove_bidi_markers(&s)).collect();
    eprintln!("{:?}", naive_lines);
}
