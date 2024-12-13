use std::io::{self, BufRead};

use itertools::Itertools;
use regex::Regex;

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(u32, u32);

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

impl Crd {
    fn mul_by(&self, n: u32) -> Crd {
        Crd(self.0 * n, self.1 * n)
    }
}

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Machine {
    da: Crd,
    db: Crd,
    prize: Crd,
}

fn parse_dbutton(s: &str) -> Crd {
    let re = Regex::new(r"^Button .: X\+(\d+), Y\+(\d+)$").unwrap();
    let caps = re.captures(s).unwrap();
    Crd(caps[1].parse().unwrap(), caps[2].parse().unwrap())
}

fn parse_prize(s: &str) -> Crd {
    let re = Regex::new(r"^Prize: X=(\d+), Y=(\d+)$").unwrap();
    let caps = re.captures(s).unwrap();
    Crd(caps[1].parse().unwrap(), caps[2].parse().unwrap())
}

fn parse_machine(tri: &[String]) -> Machine {
    eprintln!("{:?}", tri);
    assert_eq!(tri.len(), 3);
    Machine {
        da: parse_dbutton(&tri[0]),
        db: parse_dbutton(&tri[1]),
        prize: parse_prize(&tri[2]),
    }
}

const A_COST: u32 = 3;
const B_COST: u32 = 1;
const MAX_PRESSESS: u32 = 100;

impl Machine {
    fn is_steppable(&self, delta: Crd) -> bool {
        let Crd(x0, y0) = self.prize;
        let Crd(dx, dy) = delta;
        x0 % dx == 0 && y0 % dy == 0 && x0 / dx == y0 / dy
    }

    fn optimal_cost(&self) -> Option<u32> {
        let mut result = u32::MAX;
        for a in 0..=MAX_PRESSESS {
            for b in 0..=MAX_PRESSESS {
                if self.da.mul_by(a) + self.db.mul_by(b) == self.prize {
                    result = result.min(a * A_COST + b * B_COST);
                }
            }
        }
        eprintln!("{}", result);
        if result == u32::MAX {
            None
        } else {
            Some(result)
        }
    }
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().to_string())
        .filter(|line| !line.is_empty())
        .collect();

    let machines = lines
        .into_iter()
        .chunks(3)
        .into_iter()
        .map(|tri| parse_machine(&tri.collect::<Vec<_>>()))
        .collect::<Vec<_>>();

    let result = machines
        .into_iter()
        .filter_map(|m| m.optimal_cost())
        .sum::<u32>();

    println!("{}", result);
}
