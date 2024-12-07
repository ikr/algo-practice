use std::io::{self, BufRead};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i16, i16);

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
enum ProjectileStage {
    Upward { remaining: i16 },
    Horizontal { remaining: i16 },
    Downward,
}

impl ProjectileStage {
    fn next(&self, shooting_power: i16) -> Self {
        match self {
            Self::Upward { remaining: 0 } => Self::Horizontal {
                remaining: shooting_power,
            },
            Self::Upward { remaining } => Self::Horizontal {
                remaining: remaining - 1,
            },
        }
    }
}

struct Projectile {
    crd: Crd,
}

fn parse_line(s: &str) -> Crd {
    let xs = s
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect::<Vec<_>>();
    Crd(xs[0], xs[1])
}

fn main() {
    let meteors_initial: Vec<Crd> = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_line(&line.unwrap()))
        .collect();

    let catapults = vec![Crd(0, 0), Crd(0, 1), Crd(0, 2)];
    eprintln!("{:?}", catapults);

    let x_hi = meteors_initial.iter().map(|Crd(x, _)| *x).max().unwrap();
    eprintln!("max x: {}", x_hi);

    let y_hi = meteors_initial.iter().map(|Crd(_, y)| *y).max().unwrap();
    eprintln!("max y: {}", y_hi);
}
