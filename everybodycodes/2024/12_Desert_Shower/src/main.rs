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

fn simulate_tick_return_hits_ranking_score(
    mut ps: Vec<Projectile>,
    mut ms: Vec<Meteor>,
) -> (u64, Vec<Projectile>, Vec<Meteor>) {
    let mut hits_ranking_score: u64 = 0;

    ps = ps
        .into_iter()
        .map(|p| p.tick())
        .filter(|p| !p.has_landed())
        .collect();
    ps.sort_by_key(|p| p.ranking());

    let mut hit_projectiles: HashSet<Projectile> = HashSet::new();
    let mut hit_meteors: HashSet<Meteor> = HashSet::new();

    ms = ms.iter().map(|x| x.tick()).collect();

    for &m in ms.iter() {
        assert!(!m.has_landed());
        for &p in ps.iter() {
            if p.crd == m.crd {
                eprintln!("{:?} hits {:?}", p, m);
                hit_projectiles.insert(p);
                hit_meteors.insert(m);
                hits_ranking_score += p.ranking() as u64;
                break;
            }
        }
    }

    (
        hits_ranking_score,
        ps.into_iter()
            .filter(|p| !hit_projectiles.contains(p))
            .collect(),
        ms.into_iter()
            .filter(|m| !hit_meteors.contains(m))
            .collect(),
    )
}

fn main() {
    let mut ms: Vec<Meteor> = io::stdin()
        .lock()
        .lines()
        .map(|line| Meteor {
            crd: parse_line(&line.unwrap()),
        })
        .collect();

    let catapults = [Crd(0, 0), Crd(0, 1), Crd(0, 2)];

    let mut ps: Vec<Projectile> = vec![];
    let mut result: u64 = 0;

    // ps.push(Projectile::new(catapults[0], 0, 2));
    // ps.push(Projectile::new(catapults[2], 2, 2));
    // ps.push(Projectile::new(catapults[2], 2, 1));

    for t in 1..16 {
        if ms.is_empty() {
            break;
        }

        eprintln!("t = {}", t);
        let (gain, new_ps, new_ms) = simulate_tick_return_hits_ranking_score(ps, ms);
        result += gain;
        ps = new_ps;
        ms = new_ms;

        if t == 1 {
            ps.push(Projectile::new(catapults[0], 0, 2));
        }
    }

    println!("{}", result);
}
