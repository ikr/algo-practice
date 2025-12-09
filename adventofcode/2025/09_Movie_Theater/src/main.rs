use itertools::Itertools;
use std::{
    collections::{HashSet, VecDeque},
    io::{BufRead, stdin},
};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i64, i64);

impl Crd {
    fn sign(self) -> Self {
        Self(sign(self.0), sign(self.1))
    }

    fn step_direction_to(self, o: Crd) -> Crd {
        (o - self).sign()
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

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

impl std::ops::Sub<Crd> for Crd {
    type Output = Crd;

    fn sub(self, o: Crd) -> Crd {
        Crd(self.0 - o.0, self.1 - o.1)
    }
}

fn sign(x: i64) -> i64 {
    if x < 0 {
        -1
    } else if x == 0 {
        0
    } else {
        1
    }
}

fn line_a_to_b(a: Crd, b: Crd) -> Vec<Crd> {
    let delta = a.step_direction_to(b);
    let mut result = vec![a];
    let mut cur = a;

    while cur != b {
        cur = cur + delta;
        result.push(cur);
    }

    result
}

fn perimeter(corners: &[Crd]) -> HashSet<Crd> {
    corners
        .iter()
        .circular_tuple_windows()
        .flat_map(|(&a, &b)| line_a_to_b(a, b))
        .collect()
}

fn flood_fill_finite(perimeter: &HashSet<Crd>, lim: i64, start: Crd) -> Option<HashSet<Crd>> {
    assert!(!perimeter.contains(&start));
    let mut result = perimeter.clone();
    result.insert(start);
    let mut q: VecDeque<Crd> = VecDeque::from([start]);

    while let Some(u) = q.pop_front() {
        for delta in [Crd(-1, 0), Crd(0, 1), Crd(1, 0), Crd(0, -1)] {
            let v = u + delta;

            if !result.contains(&v) {
                q.push_back(v);
                result.insert(v);
                if result.len() as i64 > lim {
                    return None;
                }
            }
        }
    }

    Some(result)
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let corners: Vec<Crd> = lines.into_iter().map(|s| Crd::decode(&s)).collect();

    let lim = corners
        .iter()
        .tuple_combinations()
        .map(|(&u, &v)| (u - v).area())
        .max()
        .unwrap();

    let per = perimeter(&corners);

    for start_delta in [Crd(-1, -1), Crd(-1, 1), Crd(1, 1), Crd(1, -1)] {
        if let Some(body) = flood_fill_finite(&per, lim, corners[0] + start_delta) {
            eprintln!("{}", body.len());
        }
    }
}
