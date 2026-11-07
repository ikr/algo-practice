use itertools::{
    EitherOrBoth::{Both, Left, Right},
    Itertools,
};
use std::{
    io::{BufRead, stdin},
    ops::{Add, Mul},
};

#[derive(Clone, Copy, Debug)]
struct Plant {
    growth: usize,
    limit: usize,
}

fn vjoin<T: Add<Output = T>>(xs: Vec<T>, ys: Vec<T>) -> Vec<T> {
    xs.into_iter()
        .zip_longest(ys)
        .map(|xy| match xy {
            Both(x, y) => x + y,
            Left(a) | Right(a) => a,
        })
        .collect()
}

fn vscale<T: Mul<Output = T> + Copy>(xs: Vec<T>, k: T) -> Vec<T> {
    xs.into_iter().map(|x| x * k).collect()
}

fn decode_prefixed_int(s: &str, prefix: &str) -> usize {
    s.strip_prefix(prefix).unwrap().parse().unwrap()
}

fn decode_plant(s: String) -> Plant {
    let (_, growth_src, limit_src) = s.split(", ").collect_tuple().unwrap();
    Plant {
        growth: decode_prefixed_int(growth_src, "growth="),
        limit: decode_prefixed_int(limit_src, "limit="),
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let ps: Vec<_> = lines.into_iter().map(decode_plant).collect();
    eprintln!("{ps:?}");
}
