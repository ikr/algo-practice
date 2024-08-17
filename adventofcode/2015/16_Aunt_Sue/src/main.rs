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

fn matches_with_open_ranges_considered(a: &HashMap<String, i32>, b: &HashMap<String, i32>) -> bool {
    let keys = b.keys().collect::<Vec<_>>();
    keys.into_iter().all(|k| {
        let x = *a.get(k).unwrap_or(&0);
        let y = *b.get(k).unwrap_or(&0);
        match k.as_str() {
            "cats" | "trees" => y > x,
            "pomeranians" | "goldfish" => y < x,
            _ => y == x,
        }
    })
}

fn parse_sue_props(src: &str) -> HashMap<String, i32> {
    let re = Regex::new(r"^Sue \d+: ([a-z]+): (\d+), ([a-z]+): (\d+), ([a-z]+): (\d+)$").unwrap();
    let caps = re.captures(src).unwrap();

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

    let ts = traces_found();

    let result1 = sues
        .iter()
        .enumerate()
        .map(|(i, ps)| (i + 1, ps))
        .filter(|(_, ps)| contains_submap(&ts, ps))
        .collect::<Vec<_>>();

    eprintln!("{:?}", result1);

    let result2 = sues
        .iter()
        .enumerate()
        .map(|(i, ps)| (i + 1, ps))
        .filter(|(_, ps)| matches_with_open_ranges_considered(&ts, ps))
        .collect::<Vec<_>>();

    eprintln!("{:?}", result2);
}
