use regex::Regex;
use std::{
    collections::HashMap,
    io::{BufRead, stdin},
};

fn parse_initial_holding(s: &str) -> (String, i32) {
    let ps: Vec<_> = s.split(" HAS ").collect();
    (ps[0].to_string(), ps[1].parse().unwrap())
}

fn parse_movement(s: &str) -> (String, String, i32) {
    let re = Regex::new(r"^FROM ([A-Za-z-]+) TO ([A-Za-z-]+) AMT (\d+)$").unwrap();
    let caps = re.captures(s).unwrap();
    (
        caps[1].to_string(),
        caps[2].to_string(),
        caps[3].parse().unwrap(),
    )
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|s| s.unwrap()).collect();
    let isep: usize = lines.iter().position(|s| s.is_empty()).unwrap();

    let initial_holdings: HashMap<String, i32> = lines[..isep]
        .iter()
        .map(|s| parse_initial_holding(s))
        .collect();

    let movements: Vec<_> = lines[isep + 1..]
        .iter()
        .map(|s| parse_movement(s))
        .collect();

    let end_holdings = movements
        .into_iter()
        .fold(initial_holdings, |mut acc, (x, y, amount)| {
            let final_amount = *acc.get(&x).unwrap().min(&amount);

            acc.entry(x).and_modify(|v| *v -= final_amount);
            acc.entry(y).and_modify(|v| *v += final_amount);
            acc
        });

    let mut result: Vec<i32> = end_holdings.into_values().collect();
    result.sort_by_key(|x| -x);
    println!("{}", result[..3].iter().sum::<i32>());
}
