use itertools::Itertools;
use std::io::{BufRead, stdin};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i64, i64);

impl Crd {
    fn components(self) -> Vec<i64> {
        vec![self.0, self.1]
    }

    fn area(self) -> i64 {
        (self.0.abs() + 1) * (self.1.abs() + 1)
    }

    fn decode(s: &str) -> Self {
        let (a, b) = s
            .split(',')
            .map(|ss| ss.parse::<i64>().unwrap())
            .collect_tuple()
            .unwrap();

        Self(a, b)
    }
}

impl std::ops::Sub<Crd> for Crd {
    type Output = Crd;

    fn sub(self, o: Crd) -> Crd {
        Crd(self.0 - o.0, self.1 - o.1)
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let ps: Vec<Crd> = lines.into_iter().map(|s| Crd::decode(&s)).collect();

    let result = ps
        .into_iter()
        .tuple_combinations()
        .map(|(u, v)| (u - v).area())
        .max()
        .unwrap();
    println!("{result}");
}
