use std::io::{BufRead, stdin};

use itertools::Itertools;
use regex::Regex;

#[derive(Clone, Copy, Debug)]
struct Crd(i32, i32, i32, i32);

impl Crd {
    fn from(xs: &[i32]) -> Crd {
        Crd(xs[0], xs[1], xs[2], xs[3])
    }

    fn to_vec(self) -> Vec<i32> {
        vec![self.0, self.1, self.2, self.3]
    }
}

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1, self.2 + o.2, self.3 + o.3)
    }
}

impl std::ops::Mul<Crd> for Crd {
    type Output = Crd;

    fn mul(self, o: Crd) -> Crd {
        Crd(self.0 * o.0, self.1 * o.1, self.2 * o.2, self.3 * o.3)
    }
}

#[derive(Clone, Copy, Debug)]
struct Pred {
    coeffs: Crd,
    q: i32,
    r: i32,
}

impl Pred {
    fn eval(self, crd: Crd) -> bool {
        let s: i32 = (self.coeffs * crd).to_vec().into_iter().sum();
        ((s % self.q) + self.q) % self.q == self.r
    }
}

#[derive(Clone, Copy, Debug)]
struct Rule {
    pred: Pred,
    velocity: Crd,
}

impl Rule {
    fn parse(s: &str) -> Rule {
        let re = Regex::new(r"^RULE \d: (\d+)x\+(\d+)y\+(\d+)z\+(\d+)a DIVIDE (\d+) HAS REMAINDER (\d+) \| DEBRIS VELOCITY \((-1|0|1), (-1|0|1), (-1|0|1), (-1|0|1)\)$").unwrap();

        let nums: Vec<i32> = re
            .captures(s)
            .unwrap()
            .iter()
            .skip(1)
            .map(|c| c.unwrap().as_str())
            .map(|s| s.parse().unwrap())
            .collect();

        let coeffs = Crd::from(&nums[0..4]);
        let q = nums[4];
        let r = nums[5];
        let velocity = Crd::from(&nums[6..]);
        let pred = Pred { coeffs, q, r };
        Rule { pred, velocity }
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let rules: Vec<Rule> = lines.into_iter().map(|s| Rule::parse(&s)).collect();

    let space = [
        (0..10).collect::<Vec<i32>>(),
        (0..15).collect::<Vec<i32>>(),
        (0..60).collect::<Vec<i32>>(),
        (-1..=1).collect::<Vec<i32>>(),
    ];

    let region_counts: Vec<usize> = rules
        .into_iter()
        .map(|rule| {
            space
                .iter()
                .multi_cartesian_product()
                .filter(|xs| {
                    let ys: Vec<i32> = xs.iter().map(|x| **x).collect();
                    let p: Crd = Crd::from(&ys);
                    rule.pred.eval(p)
                })
                .count()
        })
        .collect();

    println!("{}", region_counts.into_iter().sum::<usize>());
}
