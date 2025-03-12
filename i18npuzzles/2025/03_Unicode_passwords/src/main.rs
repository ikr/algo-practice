use std::io::{self, BufRead};

fn is_allowed(s: &str) -> bool {
    let cs: Vec<char> = s.chars().collect();
    if cs.len() < 4 || cs.len() > 12 {
        return false;
    }

    cs.iter().any(|c| c.is_ascii_digit())
        && cs.iter().any(|c| c.is_uppercase())
        && cs.iter().any(|c| c.is_lowercase())
        && cs.iter().any(|c| !c.is_ascii())
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap())
        .collect();

    let result = lines.into_iter().filter(|s| is_allowed(s)).count();
    println!("{}", result);
}
