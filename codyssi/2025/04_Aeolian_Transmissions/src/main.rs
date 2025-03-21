use std::io::{self, BufRead};

fn memory_units(c: char) -> usize {
    ((c as u8) - b'A' + 1) as usize
}

fn total_memory_units(s: &str) -> usize {
    s.chars().map(memory_units).sum()
}

fn main() {
    let lines: Vec<String> = io::stdin().lock().lines().map(|s| s.unwrap()).collect();
    let result: usize = lines.into_iter().map(|s| total_memory_units(&s)).sum();
    println!("{}", result);
}
