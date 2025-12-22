use std::io::{BufRead, stdin};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i32, i32);

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

    fn scaled_by(self, k: i32) -> Self {
        Self(self.0 * k, self.1 * k)
    }

    fn mod_m_of(x: i32, m: i32) -> i32 {
        ((x % m) + m) % m
    }

    fn mod_m(self, m: i32) -> Self {
        Self(Self::mod_m_of(self.0, m), Self::mod_m_of(self.1, m))
    }

    fn in_frame(self, sky_side: i32) -> bool {
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
    let duration = 100;
    let sky_side = 1000;

    let flock: Vec<Crd> = vs
        .into_iter()
        .map(|v| v.scaled_by(duration).mod_m(sky_side))
        .collect();

    let result = flock.into_iter().filter(|a| a.in_frame(sky_side)).count();
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
