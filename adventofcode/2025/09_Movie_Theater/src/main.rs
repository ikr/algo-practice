use itertools::Itertools;
use std::io::{BufRead, stdin};

fn iof(x: bool) -> i64 {
    if x { 1 } else { 0 }
}

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i64, i64);

impl Crd {
    fn area(self) -> i64 {
        (self.0.abs() + 1) * (self.1.abs() + 1)
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
            (a.0 != b.0
                && a.1 != b.1
                && Crd::derive_all_rect_corners_from_two_diag(a, b)
                    .into_iter()
                    .all(|u| u.in_polygon(&corners)))
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
}
