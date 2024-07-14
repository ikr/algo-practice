use itertools::Itertools;
use regex::Regex;
use std::io::{self, BufRead};

fn index_of(haystack: &[String], needle: &str) -> usize {
    haystack.iter().position(|s| s == needle).unwrap()
}

fn distinct<T: Ord>(mut xs: Vec<T>) -> Vec<T> {
    xs.sort();
    xs.dedup();
    xs
}

fn parse_relative_happiness(src: &str) -> (String, String, i32) {
    let re = Regex::new(
        r"^([A-Z][a-z]+) would (gain|lose) (\d+) happiness units by sitting next to ([A-Z][a-z]+).$",
    )
    .unwrap();

    let caps = re.captures(src).unwrap();
    let u: String = caps[1].to_string();
    let v: String = caps[4].to_string();

    let sign = if caps[2] == *"lose" { -1 } else { 1 };
    let x: i32 = caps[3].parse().unwrap();

    (u, v, sign * x)
}

fn main() {
    let facts: Vec<_> = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_relative_happiness(&line.unwrap()))
        .collect();

    let mut names: Vec<String> = distinct(facts.iter().fold(vec![], |mut acc, (u, v, _)| {
        acc.push(u.to_string());
        acc.push(v.to_string());
        acc
    }));
    names.push("Ivan".to_string());
    names.sort();

    let n = names.len();
    let mut g: Vec<Vec<i32>> = vec![vec![0; n]; n];

    for (a, b, happiness) in facts.into_iter() {
        let u = index_of(&names, &a);
        let v = index_of(&names, &b);
        g[u][v] = happiness;
    }

    let mut result = 0;
    for perm in (0..n).permutations(n) {
        let candidate = (0..n).fold(0, |acc, i| {
            let u = perm[(i + n - 1) % n];
            let v = perm[i];
            let w = perm[(i + 1) % n];
            acc + g[v][u] + g[v][w]
        });
        result = result.max(candidate);
    }
    println!("{}", result);
}
