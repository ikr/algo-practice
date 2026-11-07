use itertools::Itertools;
use std::io::{BufRead, stdin};

fn decode_prefixed_int(s: &str, prefix: &str) -> usize {
    s.strip_prefix(prefix).unwrap().parse().unwrap()
}

fn decode_growth_and_limit(s: String) -> (usize, usize) {
    let (_, growth_src, limit_src) = s.split(", ").collect_tuple().unwrap();
    (
        decode_prefixed_int(growth_src, "growth="),
        decode_prefixed_int(limit_src, "limit="),
    )
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let gls: Vec<_> = lines.into_iter().map(decode_growth_and_limit).collect();
    eprintln!("{gls:?}");
}
