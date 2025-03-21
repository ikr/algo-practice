use itertools::Itertools;
use std::io::{self, BufRead};

#[derive(Clone, Copy, Debug, PartialEq)]
struct Itvl(i32, i32);

impl Itvl {
    fn intersection(&self, other: Itvl) -> Option<Itvl> {
        let Itvl(a, b) = *self;
        let Itvl(c, d) = other;
        if b < c || d < a {
            None
        } else {
            let mut xs = [a, b, c, d];
            xs.sort();
            Some(Itvl(xs[1], xs[2]))
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

fn two_intersection_size(itvls: [Itvl; 2]) -> i32 {
    let [ab, cd] = itvls;
    if let Some(itvl) = ab.intersection(cd) {
        itvl.len()
    } else {
        0
    }
}

fn without<T: PartialEq + Clone>(xs: &[T], ys: &[T]) -> Vec<T> {
    xs.iter().filter(|x| !ys.contains(&x)).cloned().collect()
}

fn single<T: Clone>(xs: &[T]) -> Option<T> {
    xs.first().cloned()
}

fn three_intersection_size(itvls: [Itvl; 3]) -> i32 {
    for (&ab, &cd) in itvls.iter().tuple_combinations() {
        if let Some(xy) = ab.intersection(cd) {
            if let Some(pq) = single(&without(&itvls, &[ab, cd])) {
                return two_intersection_size([xy, pq]);
            } else {
                return xy.len();
            }
        }
    }
    0
}

fn four_union_size(itvls: [Itvl; 4]) -> i32 {
    itvls.iter().map(|itvl| itvl.len()).sum::<i32>()
        - itvls
            .iter()
            .cloned()
            .combinations(2)
            .map(|itvls| two_intersection_size(itvls.try_into().unwrap()))
            .sum::<i32>()
        + itvls
            .iter()
            .cloned()
            .combinations(3)
            .map(|itvls| three_intersection_size(itvls.try_into().unwrap()))
            .sum::<i32>()
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

    println!("{:?}", candidates);
}
