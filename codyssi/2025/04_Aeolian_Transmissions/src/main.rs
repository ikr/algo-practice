use std::io::{self, BufRead};

fn memory_units(c: char) -> usize {
    if c.is_ascii_digit() {
        ((c as u8) - b'0') as usize
    } else {
        ((c as u8) - b'A' + 1) as usize
    }
}

fn total_memory_units(s: &str) -> usize {
    s.chars().map(memory_units).sum()
}

fn compress(s: &str) -> String {
    let n = s.len();
    let m = n / 10;
    let infix = (n - 2 * m).to_string();
    s[..m].to_string() + &infix + &s[n - m..]
}

fn main() {
    let lines: Vec<String> = io::stdin().lock().lines().map(|s| s.unwrap()).collect();
    let compressed: Vec<String> = lines.into_iter().map(|s| compress(&s)).collect();
    let result: usize = compressed.into_iter().map(|s| total_memory_units(&s)).sum();
    println!("{}", result);
}
