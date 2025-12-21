use itertools::Itertools;
use std::{
    io::{BufRead, stdin},
    iter::once,
};

#[derive(Clone, Copy, Debug)]
struct Crd(i32, i32);

impl Crd {
    fn chebyshev_distance(self, o: Crd) -> i32 {
        self.0.abs_diff(o.0).max(self.1.abs_diff(o.1)) as i32
    }

    fn decode(s: &str) -> Self {
        let (x, y) = s
            .split(',')
            .map(|sub| sub.parse().unwrap())
            .collect_tuple()
            .unwrap();

        Self(x, y)
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let crds: Vec<Crd> = lines.into_iter().map(|s| Crd::decode(&s)).collect();

    let result: i32 = once(Crd(0, 0))
        .chain(crds)
        .tuple_windows()
        .map(|(p, q)| p.chebyshev_distance(q))
        .sum();
    println!("{result}");
}
