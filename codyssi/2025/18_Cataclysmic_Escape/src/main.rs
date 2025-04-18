use std::{
    collections::HashMap,
    io::{BufRead, stdin},
};

use itertools::Itertools;
use regex::Regex;

const MX: i32 = 10;
const MY: i32 = 15;
const MZ: i32 = 60;
const MA: i32 = 3;
const TLIM: usize = 500;
const HLIM: usize = 4;

#[derive(Clone, Copy, Debug, Eq, Hash, Ord, PartialEq, PartialOrd)]
struct Crd(i32, i32, i32, i32);

impl Crd {
    fn from(xs: &[i32]) -> Crd {
        Crd(xs[0], xs[1], xs[2], xs[3])
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

fn time_to_safety(debris_points_by_time: &[HashMap<Crd, usize>]) -> usize {
    let mx = MX as usize;
    let my = MY as usize;
    let mz = MZ as usize;

    let proto = vec![vec![vec![vec![false; 4]; mz]; my]; mx];
    let mut dp: Vec<Vec<Vec<Vec<bool>>>> = proto.clone();
    dp[0][0][0][0] = true;

    for (t, debris) in debris_points_by_time.iter().enumerate().skip(1) {
        let mut dq = proto.clone();

        for x in 0..mx {
            for y in 0..my {
                for z in 0..mz {
                    for hits in 0..HLIM {
                        if !dp[x][y][z][hits] {
                            continue;
                        }

                        let u = Crd(x as i32, y as i32, z as i32, 1);
                        {
                            let hnew: usize = *debris.get(&u).unwrap_or(&0);

                            if (x, y, z) == (0, 0, 0) {
                                dq[x][y][z][hits] = true;
                            } else if hits + hnew < HLIM {
                                dq[x][y][z][hits + hnew] = true;
                            }
                        }

                        for v in u.adjacent() {
                            let Crd(vx, vy, vz, _) = v;
                            let hnew: usize = *debris.get(&v).unwrap_or(&0);

                            if (vx, vy, vz) == (0, 0, 0) {
                                dq[vx as usize][vy as usize][vz as usize][hits] = true;
                            } else if hits + hnew < HLIM {
                                dq[vx as usize][vy as usize][vz as usize][hits + hnew] = true;
                            }
                        }
                    }
                }
            }
        }

        dp = dq;
        if dp[mx - 1][my - 1][mz - 1].iter().any(|x| *x) {
            return t;
        }
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

    let debris_points_by_time: Vec<HashMap<Crd, usize>> = (0..TLIM)
        .scan(all_debris, |state, _| {
            for d in state.iter_mut() {
                *d = d.tick();
            }
            Some(state.clone())
        })
        .map(|ds| ds.iter().map(|d| d.p).counts())
        .collect();

    println!("{}", time_to_safety(&debris_points_by_time) + 1);
}
