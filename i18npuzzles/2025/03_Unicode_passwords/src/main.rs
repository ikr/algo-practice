use std::io::{self, BufRead};

fn is_allowed(s: &str) -> bool {
    let n = s.chars().count();
    if n < 4 || n > 12 {
        return false;
    }

    let cs: Vec<char> = s.chars().collect();
    cs.iter().any(|c| c.is_digit(10))
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

    let result = lines.into_iter().filter(|s| is_allowed(&s)).count();
    println!("{}", result);
}
