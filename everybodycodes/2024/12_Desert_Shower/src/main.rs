use std::{
    collections::HashMap,
    io::{self, BufRead},
};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i16, i16);

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
enum ProjectilePhase {
    Upward { remaining: u16 },
    Horizontal { remaining: u16 },
    Downward,
}

impl ProjectilePhase {
    fn new(shooting_power: u16) -> Self {
        Self::Upward {
            remaining: shooting_power,
        }
    }

    fn tick(&self, shooting_power: u16) -> Self {
        match self {
            Self::Upward { remaining: 1 } => Self::Horizontal {
                remaining: shooting_power,
            },
            Self::Upward { remaining } => Self::Upward {
                remaining: remaining - 1,
            },
            Self::Horizontal { remaining: 1 } => Self::Downward,
            Self::Horizontal { remaining } => Self::Horizontal {
                remaining: remaining - 1,
            },
            Self::Downward => Self::Downward,
        }
    }
}

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Projectile {
    t: u16,
    catapult_index: u8,
    shooting_power: u16,
    crd: Crd,
    phase: ProjectilePhase,
}

impl Projectile {
    fn new(catapult_crd: Crd, catapult_index: usize, shooting_power: u16) -> Self {
        Self {
            t: 0,
            catapult_index: catapult_index as u8,
            shooting_power,
            crd: catapult_crd,
            phase: ProjectilePhase::new(shooting_power),
        }
    }

    fn tick(&self) -> Self {
        let crd = match self.phase {
            ProjectilePhase::Upward { .. } => self.crd + Crd(1, 1),
            ProjectilePhase::Horizontal { .. } => self.crd + Crd(1, 0),
            ProjectilePhase::Downward => self.crd + Crd(1, -1),
        };

        let phase = self.phase.tick(self.shooting_power);
        Self {
            t: self.t + 1,
            catapult_index: self.catapult_index,
            shooting_power: self.shooting_power,
            crd,
            phase,
        }
    }

    fn has_landed(&self) -> bool {
        self.crd.1 == -1
    }

    fn ranking(&self) -> u16 {
        (self.catapult_index as u16 + 1) * self.shooting_power
    }
}

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Meteor {
    crd: Crd,
}

impl Meteor {
    fn tick(&self) -> Self {
        let crd = self.crd + Crd(-1, -1);
        Self { crd }
    }

    fn has_landed(&self) -> bool {
        self.crd.1 == -1
    }
}

fn parse_line(s: &str) -> Crd {
    let xs = s
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect::<Vec<_>>();
    Crd(xs[0], xs[1])
}

fn max_coordinate(ms: &[Meteor]) -> i16 {
    ms.iter().map(|m| m.crd.0.max(m.crd.1)).max().unwrap()
}

fn main() {
    let ms: Vec<Meteor> = io::stdin()
        .lock()
        .lines()
        .map(|line| Meteor {
            crd: parse_line(&line.unwrap()),
        })
        .collect();

    let hi = max_coordinate(&ms) / 2 + 1;
    let catapults = [Crd(0, 0), Crd(0, 1), Crd(0, 2)];

    let mut projectiles_by_crd: HashMap<Crd, Vec<Projectile>> = HashMap::new();
    for (index, catapult) in catapults.into_iter().enumerate() {
        for shooting_power in 1..=hi {
            let mut p = Projectile::new(catapult, index, shooting_power as u16);
            while !p.has_landed() {
                projectiles_by_crd.entry(p.crd).or_default().push(p);
                p = p.tick();
            }
        }
    }

    for (_, ps) in projectiles_by_crd.iter_mut() {
        ps.sort_by_key(|p| (p.ranking(), p.t))
    }

    let mut result: u64 = 0;
    for (im, m0) in ms.into_iter().enumerate() {
        let mut m = m0;
        for t in 0..=hi * 2 {
            let mut hit = false;

            if let Some(ps) = projectiles_by_crd.get(&m.crd) {
                for p in ps.iter() {
                    if p.t <= t as u16 {
                        result += p.ranking() as u64;
                        hit = true;
                        break;
                    }
                }
            }

            if hit {
                break;
            }

            m = m.tick();
            if m.has_landed() {
                panic!("Missed meter {}", im);
            }
        }
    }
    println!("{}", result);
}
