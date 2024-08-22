use std::{
    collections::HashSet,
    io::{self, BufRead},
};

fn all_replacements(xs: &str, pattern: &str, replacement: &str) -> Vec<String> {
    let m = pattern.len();
    let ii = xs.match_indices(pattern);
    ii.into_iter()
        .map(|(i, _)| xs[0..i].to_owned() + replacement + &xs[i + m..])
        .collect::<Vec<_>>()
}

fn parse_rule(rule_line: &str) -> (String, String) {
    let parts = rule_line.split(" => ").collect::<Vec<_>>();
    (parts[0].to_owned(), parts[1].to_owned())
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap())
        .collect();

    let medicine_molecule = lines.last().unwrap().clone();
    let rule_lines = &lines[0..(lines.len() - 2)];

    let rules = rule_lines
        .iter()
        .map(|rule_line| parse_rule(rule_line))
        .collect::<Vec<_>>();

    let xs: HashSet<String> = rules
        .into_iter()
        .flat_map(|(a, b)| all_replacements(&medicine_molecule, &a, &b))
        .collect();

    println!("{}", xs.len());
}
