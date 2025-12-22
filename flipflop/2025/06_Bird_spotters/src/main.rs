use std::io::{BufRead, stdin};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i64, i64);

impl Crd {
    fn decode(s: &str) -> Self {
        let [x, y] = s
            .split(',')
            .map(|sub| sub.parse().unwrap())
            .collect::<Vec<_>>()
            .try_into()
            .unwrap();

        Self(x, y)
    }

    fn scaled_by(self, k: i64) -> Self {
        Self(self.0 * k, self.1 * k)
    }

    fn mod_m_of(x: i64, m: i64) -> i64 {
        ((x % m) + m) % m
    }

    fn mod_m(self, m: i64) -> Self {
        Self(Self::mod_m_of(self.0, m), Self::mod_m_of(self.1, m))
    }

    fn in_frame(self, sky_side: i64) -> bool {
        let xy = [self.0, self.1];
        xy.into_iter()
            .all(|a| sky_side / 4 <= a && a < (3 * sky_side) / 4)
    }
}

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let vs: Vec<Crd> = lines.into_iter().map(|s| Crd::decode(&s)).collect();
    let period = 31556926;
    let periods_num = 1000;
    let sky_side = 1000;

    let mut flock = vec![Crd(0, 0); vs.len()];
    let mut result = 0;

    for _ in 0..periods_num {
        flock = vs
            .iter()
            .zip(flock)
            .map(|(v, a)| (a + v.scaled_by(period).mod_m(sky_side)).mod_m(sky_side))
            .collect();

        result += flock.iter().filter(|a| a.in_frame(sky_side)).count()
    }
    println!("{result}");
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_in_frame() {
        for (crd, exp) in [
            (Crd(0, 0), false),
            (Crd(1, 2), false),
            (Crd(2, 1), false),
            (Crd(2, 2), true),
            (Crd(2, 5), true),
            (Crd(5, 5), true),
            (Crd(5, 6), false),
            (Crd(6, 5), false),
            (Crd(7, 7), false),
        ] {
            assert_eq!(crd.in_frame(8), exp);
        }
    }
}
