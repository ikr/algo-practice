use std::io::{self, BufRead};

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap())
        .collect();

    let medicine_molecule = lines.last().unwrap().clone();
    eprintln!("{}", medicine_molecule);

    let rule_lines = &lines[0..(lines.len() - 2)];
    eprintln!("{:?}", rule_lines);
}
