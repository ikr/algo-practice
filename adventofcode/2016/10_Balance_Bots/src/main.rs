use regex::Regex;
use std::io::{self, BufRead};

const N: usize = 250;
const SINK_OFFSET: usize = 210;

fn decode_a_pair_of_edges(src: &str) -> (usize, [usize; 2]) {
    let re =
        Regex::new(r"^bot (\d+) gives low to (bot|output) (\d+) and high to (bot|output) (\d+)$")
            .unwrap();
    let caps = re.captures(src).unwrap();
    let offset_a = if caps[2] == *"output" { SINK_OFFSET } else { 0 };
    let offset_b = if caps[4] == *"output" { SINK_OFFSET } else { 0 };
    (
        caps[1].parse().unwrap(),
        [
            caps[3].parse::<usize>().unwrap() + offset_a,
            caps[5].parse::<usize>().unwrap() + offset_b,
        ],
    )
}

fn decode_chip_source(src: &str) -> (u8, usize) {
    let re = Regex::new(r"^value (\d+) goes to bot (\d+)$").unwrap();
    let caps = re.captures(src).unwrap();
    (caps[1].parse().unwrap(), caps[2].parse().unwrap())
}

struct Graph {
    chips: Vec<Vec<u8>>,
    adjacent: Vec<Vec<usize>>,
}

impl Graph {
    fn new() -> Graph {
        Graph {
            chips: vec![vec![]; N],
            adjacent: vec![vec![]; N],
        }
    }

    fn connect(&mut self, u: usize, v_lo: usize, v_hi: usize) {
        self.adjacent[u] = vec![v_lo, v_hi];
    }

    fn is_sink(u: usize) -> bool {
        u >= SINK_OFFSET
    }

    fn place_chip(&mut self, u: usize, c: u8) {
        self.chips[u].push(c);
        assert!(self.chips[u].len() <= 2);
        self.chips[u].sort();
    }

    fn propagate_chips(&mut self, u: usize) {
        if !Self::is_sink(u) && self.chips[u].len() == 2 {
            let [v_lo, v_hi] = self.adjacent[u][..] else {
                panic!("{:?} adjacent to {}", self.adjacent[u], u);
            };

            self.propagate_chips(v_lo);
            self.propagate_chips(v_hi);

            let [c_lo, c_hi] = self.chips[u][..] else {
                panic!("How come the length of {:?} was 2?", self.chips[u]);
            };

            if c_lo == 17 && c_hi == 61 {
                println!("Result 1: {}", u);
            }

            self.place_chip(v_lo, c_lo);
            self.place_chip(v_hi, c_hi);
            self.chips[u].clear();

            self.propagate_chips(v_lo);
            self.propagate_chips(v_hi);
        }
    }
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

    let chip_source_lines: Vec<String> = lines
        .into_iter()
        .filter(|x| x.starts_with("value "))
        .map(|x| x.to_owned())
        .collect();

    let mut g = Graph::new();
    for line in adjacency_lines {
        let (u, [v_lo, v_hi]) = decode_a_pair_of_edges(&line);
        g.connect(u, v_lo, v_hi);
    }

    for line in chip_source_lines {
        let (c, u) = decode_chip_source(&line);
        g.place_chip(u, c);
        g.propagate_chips(u);
    }

    let mut result: u32 = 1;
    for i in 0..3 {
        for c in g.chips[SINK_OFFSET + i].iter() {
            result *= *c as u32;
        }
    }
    println!("Result 2: {}", result);
}
