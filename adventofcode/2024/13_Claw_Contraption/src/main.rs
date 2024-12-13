use std::io::{self, BufRead};

use itertools::Itertools;
use regex::Regex;

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i64, i64);

const A_COST: i64 = 3;
const B_COST: i64 = 1;
const ADDENDUM: i64 = 10000000000000;

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

impl Crd {
    fn mul_by(&self, n: i64) -> Crd {
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
    Crd(
        ADDENDUM + caps[1].parse::<i64>().unwrap(),
        ADDENDUM + caps[2].parse::<i64>().unwrap(),
    )
}

fn parse_machine(tri: &[String]) -> Machine {
    assert_eq!(tri.len(), 3);
    Machine {
        da: parse_dbutton(&tri[0]),
        db: parse_dbutton(&tri[1]),
        prize: parse_prize(&tri[2]),
    }
}

impl Machine {
    fn optimal_cost(&self) -> Option<i64> {
        let Crd(dxa, dya) = self.da;
        let Crd(dxb, dyb) = self.db;
        let Crd(x0, y0) = self.prize;

        let kap = x0 * dyb - y0 * dxb;
        let kaq = dxa * dyb - dya * dxb;
        if kaq == 0 || kap % kaq != 0 {
            return None;
        }

        let ka = kap / kaq;
        if ka < 0 {
            return None;
        }

        let kbp = y0 - ka * dya;
        if kbp % dyb != 0 {
            return None;
        }
        let kb = kbp / dyb;

        Some(ka * A_COST + kb * B_COST)
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
        .map(|m| {
            eprintln!("{:?}", m.optimal_cost());
            m
        })
        .filter_map(|m| m.optimal_cost())
        .sum::<i64>();

    println!("{}", result);
}
