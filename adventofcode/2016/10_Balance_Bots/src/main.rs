use regex::Regex;
use std::io::{self, BufRead};

fn decode_a_pair_of_edges(src: &str) -> (u8, [u8; 2]) {
    let re = Regex::new(r"^bot (\d+) gives low to bot (\d+) and high to bot (\d+)$").unwrap();
    let caps = re.captures(src).unwrap();
    eprintln!("{:?}", caps);
    (
        caps[1].parse().unwrap(),
        [caps[2].parse().unwrap(), caps[3].parse().unwrap()],
    )
}

struct Graph {
    chips: Vec<Vec<u8>>,
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap())
        .collect();

    let adjacency_lines: Vec<String> = lines
        .iter()
        .filter(|x| x.starts_with("bot "))
        .map(|x| x.to_owned())
        .collect();

    let source_lines: Vec<String> = lines
        .into_iter()
        .filter(|x| x.starts_with("value "))
        .map(|x| x.to_owned())
        .collect();

    eprintln!(
        "{:?}",
        adjacency_lines
            .iter()
            .map(|x| decode_a_pair_of_edges(&x))
            .collect::<Vec<_>>()
    );
}
