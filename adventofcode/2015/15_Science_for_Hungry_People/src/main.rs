use itertools::Itertools;
use regex::Regex;
use std::io::{self, BufRead};

const TOTAL_SPOONS: i8 = 100;

fn parse_fact(src: &str) -> (String, [i8; 5]) {
    let re = Regex::new(r"^([A-Z][a-z]+): capacity (-?\d+), durability (-?\d+), flavor (-?\d+), texture (-?\d+), calories (-?\d+)$").unwrap();
    let caps = re.captures(src).unwrap();
    (
        caps[1].to_string(),
        caps.iter()
            .skip(2)
            .map(|x| x.unwrap().as_str().parse::<i8>().unwrap())
            .collect::<Vec<_>>()
            .try_into()
            .unwrap(),
    )
}

fn all_ratios(ingridients_count: usize) -> Vec<Vec<i8>> {
    assert!(ingridients_count > 1);
    (1..ingridients_count)
        .map(|_| (1..TOTAL_SPOONS as i64).collect::<Vec<_>>())
        .multi_cartesian_product()
        .filter(|xs| xs.iter().sum::<i64>() < 100)
        .map(|xs| {
            let mut v = xs.iter().map(|x| *x as i8).collect::<Vec<_>>();
            let s = v.iter().sum::<i8>();
            v.push(TOTAL_SPOONS - s);
            v
        })
        .collect()
}

fn main() {
    let facts: Vec<_> = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_fact(&line.unwrap()))
        .collect();
    eprintln!("{:?}", facts);

    eprintln!("{:?}", all_ratios(2));
}
