use regex::Regex;
use std::{
    collections::HashMap,
    io::{self, BufRead},
};

fn room_code_parts(src: &str) -> Vec<String> {
    Regex::new(r"[a-z0-9]+")
        .unwrap()
        .find_iter(src)
        .map(|x| x.as_str().to_string())
        .collect()
}

fn all_room_letters(rcp: &[String]) -> Vec<char> {
    let n = rcp.len();
    rcp[0..n - 2].iter().fold(vec![], |mut acc, s| {
        acc.extend(s.chars());
        acc
    })
}

fn room_checksum(rcp: &[String]) -> String {
    rcp.iter().last().unwrap().to_string()
}

fn room_id(rcp: &[String]) -> u32 {
    let n = rcp.len();
    rcp[n - 2].parse().unwrap()
}

fn frequencies(xs: &[char]) -> HashMap<char, u8> {
    xs.iter().fold(HashMap::new(), |mut acc, c| {
        acc.entry(*c).and_modify(|f| *f += 1).or_insert(1);
        acc
    })
}

fn letters_checksum(xs: &[char]) -> String {
    let mut ps: Vec<(i8, char)> = frequencies(xs)
        .into_iter()
        .map(|(k, v)| (-1 * v as i8, k))
        .collect();
    ps.sort();

    ps[0..5].into_iter().map(|(_, c)| c).collect()
}

fn main() {
    let xss: Vec<Vec<String>> = io::stdin()
        .lock()
        .lines()
        .map(|line| room_code_parts(&line.unwrap()))
        .collect();

    let result: u32 = xss
        .into_iter()
        .filter(|xs| letters_checksum(&all_room_letters(&xs)) == room_checksum(&xs))
        .map(|xs| room_id(&xs))
        .sum();
    println!("{}", result);
}
