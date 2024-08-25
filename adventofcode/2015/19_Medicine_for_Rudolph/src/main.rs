use std::{
    collections::HashSet,
    io::{self, BufRead},
};

fn all_replacements(xs: &str, pattern: &str, replacement: &str) -> Vec<String> {
    let m = pattern.len();
    xs.match_indices(pattern)
        .into_iter()
        .map(|(i, _)| xs[0..i].to_owned() + replacement + &xs[i + m..])
        .collect::<Vec<_>>()
}

fn parse_rule(rule_line: &str) -> (String, String) {
    let parts = rule_line.split(" => ").collect::<Vec<_>>();
    (parts[0].to_owned(), parts[1].to_owned())
}

fn solve_part_1(medicine_molecule: &str, rules: &[(String, String)]) -> usize {
    rules
        .iter()
        .flat_map(|(a, b)| all_replacements(medicine_molecule, a, b))
        .collect::<HashSet<_>>()
        .len()
}

fn replace_first(xs: &str, pattern: &str, replacement: &str) -> String {
    let m = pattern.len();
    let i = xs.find(pattern).unwrap();
    xs[0..i].to_owned() + replacement + &xs[i + m..]
}

fn suggest_rule_for_deflation(
    medicine_molecule: &str,
    rules: &[(String, String)],
) -> Option<(String, String)> {
    rules
        .iter()
        .filter(|(_, inflated)| medicine_molecule.contains(inflated))
        .max_by_key(|(deflated, inflated)| inflated.len() - deflated.len())
        .cloned()
}

fn solve_part_2(medicine_molecule: &str, rules: &[(String, String)]) -> u16 {
    eprintln!("{}", medicine_molecule);

    let mut xs = medicine_molecule.to_owned();
    let mut result: u16 = 0;

    while let Some((deflated, inflated)) = suggest_rule_for_deflation(&xs, rules) {
        xs = replace_first(&xs, &inflated, &deflated);
        result += 1;
        eprintln!("{} → {}: {}", inflated, deflated, xs);
    }

    result
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

    println!("{}", solve_part_1(&medicine_molecule, &rules));
    println!("{}", solve_part_2(&medicine_molecule, &rules));
}
