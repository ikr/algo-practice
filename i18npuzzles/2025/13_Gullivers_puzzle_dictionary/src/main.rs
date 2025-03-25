use std::io::{self, BufRead};

fn word_source_to_bytes(s: &str) -> Vec<u8> {
    s.as_bytes()
        .chunks(2)
        .map(|ab| u8::from_str_radix(core::str::from_utf8(ab).unwrap(), 16).unwrap())
        .collect()
}

fn main() {
    let lines: Vec<String> = io::stdin().lock().lines().map(|s| s.unwrap()).collect();
    let isep = lines.iter().position(|s| s.is_empty()).unwrap();

    let word_bytes: Vec<Vec<u8>> = lines[..isep]
        .iter()
        .map(|s| word_source_to_bytes(s))
        .collect();
    eprintln!("{:?}", word_bytes);

    let patterns: Vec<String> = lines[isep + 1..]
        .iter()
        .map(|s| s.trim().to_string())
        .collect();
    eprintln!("{:?}", patterns);
}
