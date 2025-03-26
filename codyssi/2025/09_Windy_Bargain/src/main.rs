use itertools::Itertools;
use regex::Regex;
use std::{
    collections::{HashMap, VecDeque},
    io::{BufRead, stdin},
};

fn parse_initial_holding(s: &str) -> (String, u32) {
    let ps: Vec<_> = s.split(" HAS ").collect();
    (ps[0].to_string(), ps[1].parse().unwrap())
}

fn parse_movement(s: &str) -> (String, String, u32) {
    let re = Regex::new(r"^FROM ([A-Za-z-]+) TO ([A-Za-z-]+) AMT (\d+)$").unwrap();
    let caps = re.captures(s).unwrap();
    (
        caps[1].to_string(),
        caps[2].to_string(),
        caps[3].parse().unwrap(),
    )
}

struct Ledger {
    ids: HashMap<String, usize>,
    holdings: Vec<u32>,
    ious: Vec<VecDeque<(usize, u32)>>,
}

impl Ledger {
    fn from(holdings_by_name: HashMap<String, u32>) -> Self {
        let ids: HashMap<String, usize> = holdings_by_name
            .keys()
            .sorted()
            .cloned()
            .enumerate()
            .map(|(i, name)| (name, i))
            .collect();

        let holdings: Vec<u32> =
            holdings_by_name
                .into_iter()
                .fold(vec![0; ids.len()], |mut acc, (name, amount)| {
                    acc[*ids.get(&name).unwrap()] = amount;
                    acc
                });

        let ious: Vec<VecDeque<(usize, u32)>> = vec![VecDeque::new(); ids.len()];
        Self {
            ids,
            holdings,
            ious,
        }
    }

    fn id(&self, name: &str) -> usize {
        *self.ids.get(name).unwrap()
    }

    fn result(&self) -> u32 {
        self.holdings.iter().filter(|&&x| x != 0).k_largest(3).sum()
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|s| s.unwrap()).collect();
    let isep: usize = lines.iter().position(|s| s.is_empty()).unwrap();

    let mut holdings: HashMap<String, u32> = lines[..isep]
        .iter()
        .map(|s| parse_initial_holding(s))
        .collect();

    let movements: Vec<_> = lines[isep + 1..]
        .iter()
        .map(|s| parse_movement(s))
        .collect();

    todo!()
}
