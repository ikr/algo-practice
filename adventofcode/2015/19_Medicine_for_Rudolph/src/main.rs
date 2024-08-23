use std::hash::{DefaultHasher, Hash, Hasher};
use std::{
    collections::{HashSet, VecDeque},
    io::{self, BufRead},
    process::exit,
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

fn mhash(xs: &str) -> u64 {
    let mut hasher = DefaultHasher::new();
    xs.hash(&mut hasher);
    hasher.finish()
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

    let result1: HashSet<String> = rules
        .iter()
        .flat_map(|(a, b)| all_replacements(&medicine_molecule, &a, &b))
        .collect();

    println!("{}", result1.len());

    let mut q: VecDeque<(String, i32)> = VecDeque::new();
    q.push_back(("e".to_owned(), 0));

    let mut seen: HashSet<u64> = HashSet::new();
    seen.insert(mhash("e"));

    while let Some((u, d)) = q.pop_front() {
        let vs: HashSet<String> = rules
            .iter()
            .flat_map(|(a, b)| all_replacements(&u, &a, &b))
            .filter(|v| v.len() <= medicine_molecule.len() && !seen.contains(&mhash(v)))
            .collect();

        for v in vs {
            if v == medicine_molecule {
                println!("{}", d + 1);
                exit(0);
            }

            q.push_back((v.clone(), d + 1));
            seen.insert(mhash(&v));
        }
    }
}
