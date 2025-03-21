use itertools::Itertools;
use std::io::{self, BufRead};

#[derive(Clone, Copy, Debug)]
struct Itvl(i32, i32);

impl Itvl {
    fn intersection(&self, other: Itvl) -> Option<Itvl> {
        let Itvl(a, b) = *self;
        let Itvl(c, d) = other;
        if b < c || d < a {
            None
        } else {
            Some(Itvl(a.max(c), b.min(d)))
        }
    }

    fn len(&self) -> i32 {
        self.1 - self.0 + 1
    }
}

fn parse_interval(s: &str) -> Itvl {
    let ab: Vec<i32> = s.split('-').map(|s| s.parse().unwrap()).collect();
    Itvl(ab[0], ab[1])
}

fn parse_line(s: &str) -> [Itvl; 2] {
    s.split_ascii_whitespace()
        .map(parse_interval)
        .collect::<Vec<_>>()
        .try_into()
        .unwrap()
}

fn intersection_size(itvls: &[Itvl]) -> i32 {
    match itvls
        .iter()
        .skip(1)
        .try_fold(itvls[0], |acc, &ii| acc.intersection(ii))
    {
        Some(x) => x.len(),
        None => 0,
    }
}

fn four_union_size(itvls: [Itvl; 4]) -> i32 {
    itvls.iter().map(|itvl| itvl.len()).sum::<i32>()
        - itvls
            .iter()
            .cloned()
            .combinations(2)
            .map(|iis| intersection_size(&iis))
            .sum::<i32>()
        + itvls
            .iter()
            .cloned()
            .combinations(3)
            .map(|itvls| intersection_size(&itvls))
            .sum::<i32>()
        - intersection_size(&itvls)
}

fn main() {
    let lines: Vec<_> = io::stdin()
        .lock()
        .lines()
        .map(|s| parse_line(&s.unwrap()))
        .collect();

    let candidates: Vec<i32> = lines
        .windows(2)
        .map(|ab| four_union_size([ab[0][0], ab[0][1], ab[1][0], ab[1][1]]))
        .collect();

    println!("{}", candidates.iter().max().unwrap());
}
