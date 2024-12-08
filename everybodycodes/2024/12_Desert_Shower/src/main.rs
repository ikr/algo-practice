use std::{
    collections::HashSet,
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

    let mut result: u64 = 0;
    println!("{}", result);
}
