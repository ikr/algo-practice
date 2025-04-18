use std::{
    collections::{HashSet, VecDeque},
    io::{BufRead, stdin},
};

use itertools::Itertools;
use regex::Regex;

// const MX: i32 = 10;
// const MY: i32 = 15;
// const MZ: i32 = 60;
const MX: i32 = 3;
const MY: i32 = 3;
const MZ: i32 = 5;
const MA: i32 = 3;
const TLIM: usize = 5000;
const MAX_WAIT: usize = 4;

#[derive(Clone, Copy, Debug, Eq, Hash, Ord, PartialEq, PartialOrd)]
struct Crd(i32, i32, i32, i32);

impl Crd {
    fn from(xs: &[i32]) -> Crd {
        Crd(xs[0], xs[1], xs[2], xs[3])
    }

    fn zero() -> Crd {
        Crd(0, 0, 0, 0)
    }

    fn to_vec(self) -> Vec<i32> {
        vec![self.0, self.1, self.2, self.3]
    }

    fn modulize(self) -> Crd {
        Crd(
            (self.0 % MX + MX) % MX,
            (self.1 % MY + MY) % MY,
            (self.2 % MZ + MZ) % MZ,
            (self.3 % MA + MA) % MA,
        )
    }

    fn adjacent(self) -> Vec<Crd> {
        let Crd(x, y, z, _) = self;

        let rules = [
            (x > 0, Crd(-1, 0, 0, 0)),
            (x < MX - 1, Crd(1, 0, 0, 0)),
            (y > 0, Crd(0, -1, 0, 0)),
            (y < MY - 1, Crd(0, 1, 0, 0)),
            (z > 0, Crd(0, 0, -1, 0)),
            (z < MZ - 1, Crd(0, 0, 1, 0)),
        ];

        rules
            .into_iter()
            .filter_map(|(yes, delta)| if yes { Some(self + delta) } else { None })
            .collect()
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

#[derive(Clone, Copy, Debug)]
struct Debris {
    p: Crd,
    v: Crd,
}

impl Debris {
    fn tick(self) -> Self {
        Self {
            p: (self.p + self.v).modulize(),
            v: self.v,
        }
    }
}

fn time_to_safety(debris_points_by_time: &[HashSet<Crd>]) -> usize {
    let ua: (usize, Crd) = (0, Crd::zero());
    let pz = Crd(MX - 1, MY - 1, MZ - 1, 0);
    let mut visited: HashSet<Crd> = HashSet::from([Crd::zero()]);
    let mut covered: HashSet<(usize, Crd)> = HashSet::from([ua]);
    let mut q: VecDeque<(usize, Crd)> = VecDeque::from([ua]);

    while let Some((t, p)) = q.pop_front() {
        assert!(visited.contains(&p));
        if p != Crd::zero() && debris_points_by_time[t].contains(&p) {
            continue;
        }
        if p == pz {
            return t;
        }

        for pp in p.adjacent() {
            if !visited.contains(&pp) {
                visited.insert(pp);
                covered.insert((t + 1, pp));
                q.push_back((t + 1, pp));
            }
        }

        let wait_states_num = (1..=MAX_WAIT)
            .filter_map(|dt| {
                let v = (t.saturating_sub(dt), p);
                if covered.contains(&v) { Some(v) } else { None }
            })
            .unique()
            .count();

        if wait_states_num < MAX_WAIT {
            covered.insert((t + 1, p));
            q.push_back((t + 1, p));
        }
        eprintln!("{:?}", q);
    }

    panic!("Not found")
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let rules: Vec<Rule> = lines.into_iter().map(|s| Rule::parse(&s)).collect();

    let space = [
        (0..MX).collect::<Vec<i32>>(),
        (0..MY).collect::<Vec<i32>>(),
        (0..MZ).collect::<Vec<i32>>(),
        (-1..=1).collect::<Vec<i32>>(),
    ];

    let particle_regions: Vec<Vec<Debris>> = rules
        .into_iter()
        .map(|rule| {
            space
                .iter()
                .multi_cartesian_product()
                .filter_map(|xs| {
                    let ys: Vec<i32> = xs.iter().map(|x| **x).collect();
                    let p: Crd = Crd::from(&ys);
                    if rule.pred.eval(p) {
                        Some(Debris {
                            p: p + Crd(0, 0, 0, 1),
                            v: rule.velocity,
                        })
                    } else {
                        None
                    }
                })
                .collect()
        })
        .collect();

    let all_debris: Vec<Debris> = particle_regions.into_iter().flatten().collect();

    let debris_points_by_time: Vec<HashSet<Crd>> = (0..TLIM)
        .scan(all_debris, |state, _| {
            for d in state.iter_mut() {
                *d = d.tick();
            }
            Some(state.clone())
        })
        .map(|ds| ds.iter().map(|d| d.p).collect())
        .collect();

    println!("{}", time_to_safety(&debris_points_by_time));
}
