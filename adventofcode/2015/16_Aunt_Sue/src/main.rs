use std::{
    collections::HashMap,
    io::{self, BufRead},
};

use regex::Regex;

fn traces_found() -> HashMap<String, i32> {
    HashMap::from(
        [
            ("children", 3),
            ("cats", 7),
            ("samoyeds", 2),
            ("pomeranians", 3),
            ("akitas", 0),
            ("vizslas", 0),
            ("goldfish", 5),
            ("trees", 3),
            ("cars", 2),
            ("perfumes", 1),
        ]
        .map(|(k, v)| (k.to_string(), v)),
    )
}

fn contains_submap(a: &HashMap<String, i32>, b: &HashMap<String, i32>) -> bool {
    let keys = b.keys().collect::<Vec<_>>();
    keys.into_iter()
        .all(|k| a.get(k).unwrap_or(&0) == b.get(k).unwrap_or(&0))
}

fn parse_sue_props(src: &str) -> HashMap<String, i32> {
    let re = Regex::new(r"^Sue \d+: ([a-z]+): (\d+), ([a-z]+): (\d+), ([a-z]+): (\d+)$").unwrap();
    let caps = re.captures(src).unwrap();
    eprintln!("{:?}", caps);

    (0..3)
        .map(|i| {
            let j = 1 + i * 2;
            let k = j + 1;
            (caps[j].to_string(), caps[k].parse().unwrap())
        })
        .collect()
}

fn main() {
    let sues: Vec<_> = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_sue_props(&line.unwrap()))
        .collect();

    eprintln!("{:?}", sues);
}
