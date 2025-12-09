use itertools::Itertools;
use std::io::{BufRead, stdin};

fn iof(x: bool) -> i64 {
    if x { 1 } else { 0 }
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

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i64, i64);

impl Crd {
    fn area(self) -> i64 {
        (self.0.abs() + 1) * (self.1.abs() + 1)
    }

    fn mul_by(self, k: i64) -> Self {
        Self(k * self.0, k * self.1)
    }

    fn div_by(self, k: i64) -> Self {
        Self(self.0 / k, self.1 / k)
    }

    fn manhattan_dist(self, o: Crd) -> i64 {
        let delta = o - self;
        delta.0.abs() + delta.1.abs()
    }

    fn decode(s: &str) -> Self {
        let (a, b) = s
            .split(',')
            .map(|ss| ss.parse::<i64>().unwrap())
            .collect_tuple()
            .unwrap();

        Self(a, b)
    }

    fn dot(self, p: Self) -> i64 {
        self.0 * p.0 + self.1 * p.1
    }

    fn cross(self, p: Self) -> i64 {
        self.0 * p.1 - self.1 * p.0
    }

    fn cross_ab(self, a: Self, b: Self) -> i64 {
        (a - self).cross(b - self)
    }

    fn on_segment(self, s: Self, e: Self) -> bool {
        self.cross_ab(s, e) == 0 && (s - self).dot(e - self) <= 0
    }

    fn in_polygon(self, p: &[Crd]) -> bool {
        let n = p.len();
        let mut cnt = 0;

        for i in 0..n {
            let q: Crd = p[(i + 1) % n];

            if self.on_segment(p[i], q) {
                return true;
            }

            cnt ^= iof((iof(self.1 < p[i].1) - iof(self.1 < q.1)) * self.cross_ab(p[i], q) > 0);
        }

        cnt != 0
    }

    fn derive_all_rect_corners_from_two_diag(a: Crd, b: Crd) -> Vec<Crd> {
        let Crd(d0, d1) = b - a;
        vec![a, a + Crd(d0, 0), b, a + Crd(0, d1)]
    }

    fn sign(self) -> Self {
        Self(sign(self.0), sign(self.1))
    }

    fn step_direction_to(self, o: Crd) -> Crd {
        (o - self).sign()
    }

    fn trace_to(self, b: Crd) -> Vec<Crd> {
        assert!(self.0 == b.0 || self.1 == b.1);
        let delta = self.step_direction_to(b);
        let dist = self.manhattan_dist(b);

        if dist < 20 {
            let mut result = vec![self];
            let mut cur = self;

            while cur != b {
                cur = cur + delta;
                result.push(cur);
            }

            result
        } else {
            vec![
                self,
                delta.mul_by(1 * dist).div_by(5),
                delta.mul_by(2 * dist).div_by(5),
                delta.mul_by(3 * dist).div_by(5),
                delta.mul_by(4 * dist).div_by(5),
                b,
            ]
        }
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

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let corners: Vec<Crd> = lines.into_iter().map(|s| Crd::decode(&s)).collect();

    let result: i64 = corners
        .iter()
        .tuple_combinations()
        .filter_map(|(&a, &b)| {
            if a.0 != b.0 && a.1 != b.1 {
                eprintln!("Rect within {:?} - {:?}:", a, b);
            }

            (a.0 != b.0
                && a.1 != b.1
                && Crd::derive_all_rect_corners_from_two_diag(a, b)
                    .into_iter()
                    .circular_tuple_windows()
                    .all(|(p, q)| {
                        eprintln!("{:?}", (p, q));
                        p.trace_to(q).into_iter().all(|u| u.in_polygon(&corners))
                    }))
            .then_some((b - a).area())
        })
        .max()
        .unwrap();
    println!("{result}");
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_derive_all_rect_corners_from_two_diag() {
        assert_eq!(
            Crd::derive_all_rect_corners_from_two_diag(Crd(0, 0), Crd(3, 4)),
            vec![Crd(0, 0), Crd(3, 0), Crd(3, 4), Crd(0, 4)]
        );
    }

    #[test]
    fn test_line_to() {
        assert_eq!(
            Crd(0, 0).trace_to(Crd(0, 100)),
            vec![
                Crd(0, 0),
                Crd(0, 20),
                Crd(0, 40),
                Crd(0, 60),
                Crd(0, 80),
                Crd(0, 100)
            ]
        );
    }
}
