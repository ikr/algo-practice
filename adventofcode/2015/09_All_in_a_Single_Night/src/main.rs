use std::io::{self, BufRead};

use itertools::Itertools;

fn parse_line_parts(src: &str) -> (String, i32) {
    let [a, b] = src.split(" = ").collect::<Vec<_>>()[..] else {
        panic!("Invalid line {}", src)
    };
    (a.to_owned(), b.parse().unwrap())
}

fn parse_locations(src: &str) -> (String, String) {
    let [a, b] = src.split(" to ").collect::<Vec<_>>()[..] else {
        panic!("Invalid locations pair {}", src)
    };
    (a.to_owned(), b.to_owned())
}

fn parse_line(src: &str) -> (String, String, i32) {
    let (ab, distance) = parse_line_parts(src);
    let (a, b) = parse_locations(&ab);
    (a, b, distance)
}

fn index_of(haystack: &[String], needle: &str) -> usize {
    haystack.iter().position(|s| s == needle).unwrap()
}

fn distinct<T: Ord>(mut xs: Vec<T>) -> Vec<T> {
    xs.sort();
    xs.dedup();
    xs
}

fn main() {
    let facts: Vec<_> = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_line(&line.unwrap()))
        .collect();

    let locations: Vec<String> = distinct(facts.iter().fold(vec![], |mut acc, (u, v, _)| {
        acc.push(u.to_string());
        acc.push(v.to_string());
        acc
    }));

    let n = locations.len();
    let mut g: Vec<Vec<i32>> = vec![vec![0; n]; n];

    for (a, b, distance) in facts.into_iter() {
        let u = index_of(&locations, &a);
        let v = index_of(&locations, &b);
        g[u][v] = distance;
        g[v][u] = distance;
    }

    let mut result = 0;
    for perm in (0..n).permutations(n) {
        let candidate = perm.windows(2).fold(0, |acc, uv| {
            let [u, v] = uv[..] else {
                panic!("{:?} isn't a pair", uv)
            };
            acc + g[u][v]
        });
        result = result.max(candidate);
    }
    println!("{}", result);
}
