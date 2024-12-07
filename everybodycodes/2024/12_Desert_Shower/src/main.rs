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
    catapult_index: u8,
    shooting_power: u16,
    crd: Crd,
    phase: ProjectilePhase,
}

impl Projectile {
    fn new(catapult_crd: Crd, catapult_index: usize, shooting_power: u16) -> Self {
        Self {
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

fn main() {
    let mut ms: HashSet<Meteor> = io::stdin()
        .lock()
        .lines()
        .map(|line| Meteor {
            crd: parse_line(&line.unwrap()),
        })
        .collect();

    let catapults = vec![Crd(0, 0), Crd(0, 1), Crd(0, 2)];
    let highest_shooting_power: u16 = 4000;

    let mut ps: HashSet<Projectile> = catapults
        .into_iter()
        .enumerate()
        .flat_map(|(i, crd)| {
            (1..=highest_shooting_power)
                .map(|shooting_power| Projectile::new(crd, i, shooting_power))
                .collect::<HashSet<_>>()
        })
        .collect();

    let mut result: u64 = 0;
    while !ms.is_empty() {
        let mut new_ms: HashSet<Meteor> = HashSet::new();
        let mut hit_projectiles: Vec<Projectile> = vec![];

        for m0 in ms {
            let m = m0.tick();
            if m.has_landed() {
                panic!("Missed the {:?}", m);
            }

            let mut hit = false;
            for &p in ps.iter() {
                if p.crd == m.crd {
                    eprintln!("{:?} hits {:?}", p, m);
                    hit_projectiles.push(p);
                    result += p.ranking() as u64;
                    hit = true;
                    break;
                }
            }
            if !hit {
                new_ms.insert(m);
            }
        }

        for p in hit_projectiles {
            ps.remove(&p);
        }

        ms = new_ms;
        ps = ps
            .into_iter()
            .map(|p| p.tick())
            .filter(|p| !p.has_landed())
            .collect();
    }
    println!("{}", result);
}
