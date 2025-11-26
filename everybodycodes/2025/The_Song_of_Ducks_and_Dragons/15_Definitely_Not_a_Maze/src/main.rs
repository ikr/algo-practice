use itertools::Itertools;
use pathfinding::prelude::astar;
use std::{collections::HashSet, io::Read, iter::once};

#[derive(Clone, Copy, Debug)]
enum Instr {
    L(i64),
    R(i64),
}

impl Instr {
    fn decode(s: &str) -> Self {
        match s.as_bytes()[0] {
            b'L' => Self::L(s.strip_prefix('L').unwrap().parse().unwrap()),
            b'R' => Self::R(s.strip_prefix('R').unwrap().parse().unwrap()),
            _ => unreachable!(),
        }
    }
}

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i64, i64);

// Geometry functions adapted from KACTL
// https://github.com/kth-competitive-programming/kactl/tree/main/content/geometry
impl Crd {
    fn neighs(self) -> Vec<Crd> {
        Dir::all()
            .into_iter()
            .circular_tuple_windows()
            .map(|(d1, d2)| self + d1.delta() + d2.delta())
            .chain(Dir::all().into_iter().map(|d| self + d.delta()))
            .collect()
    }

    fn sgn(x: i64) -> i64 {
        if x > 0 {
            1
        } else if x < 0 {
            -1
        } else {
            0
        }
    }

    fn mul_by(self, k: i64) -> Self {
        Self(k * self.0, k * self.1)
    }

    fn div_by(self, k: i64) -> Self {
        Self(self.0 / k, self.1 / k)
    }

    fn manhattan_distance(self, p: Self) -> u64 {
        self.0.abs_diff(p.0) + self.1.abs_diff(p.1)
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

    fn on_segment(s: Self, e: Self, p: Self) -> bool {
        p.cross_ab(s, e) == 0 && (s - p).dot(e - p) <= 0
    }

    // If a unique intersection point between the line segments going from a to b and from c to d
    // exists then it is returned.
    // If no intersection point exists an empty vector is returned.
    // If infinitely many exist a vector with 2 elements is returned, containing the endpoints
    // of the common line segment.
    // The wrong position will be returned if the intersection point does not have integer
    // coordinates.
    // Products of three coordinates are used in intermediate steps so watch out for an integer
    // overflow.
    fn segments_intersection(a: Self, b: Self, c: Self, d: Self) -> Vec<Self> {
        let oa = c.cross_ab(d, a);
        let ob = c.cross_ab(d, b);
        let oc = a.cross_ab(b, c);
        let od = a.cross_ab(b, d);

        if Self::sgn(oa) * Self::sgn(ob) < 0 && Self::sgn(oc) * Self::sgn(od) < 0 {
            vec![(a.mul_by(ob) - b.mul_by(oa)).div_by(ob - oa)]
        } else {
            let mut result: HashSet<Crd> = HashSet::new();
            if Self::on_segment(c, d, a) {
                result.insert(a);
            }
            if Self::on_segment(c, d, b) {
                result.insert(b);
            }
            if Self::on_segment(a, b, c) {
                result.insert(c);
            }
            if Self::on_segment(a, b, d) {
                result.insert(d);
            }
            result.into_iter().collect()
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

#[derive(Clone, Copy, Debug)]
enum Dir {
    N,
    E,
    S,
    W,
}

impl Dir {
    fn all() -> [Self; 4] {
        [Self::N, Self::E, Self::S, Self::W]
    }

    fn delta(&self) -> Crd {
        match self {
            Dir::N => Crd(-1, 0),
            Dir::E => Crd(0, 1),
            Dir::S => Crd(1, 0),
            Dir::W => Crd(0, -1),
        }
    }

    fn turn_left(&self) -> Dir {
        match self {
            Dir::N => Dir::W,
            Dir::E => Dir::N,
            Dir::S => Dir::E,
            Dir::W => Dir::S,
        }
    }

    fn turn_right(&self) -> Dir {
        match self {
            Dir::N => Dir::E,
            Dir::E => Dir::S,
            Dir::S => Dir::W,
            Dir::W => Dir::N,
        }
    }
}

fn is_reachable(wall_segments: &[(Crd, Crd)], p: Crd) -> bool {
    !wall_segments.iter().any(|&(s, e)| Crd::on_segment(s, e, p))
}

fn is_b_reachable_from_a(wall_segments: &[(Crd, Crd)], a: Crd, b: Crd) -> bool {
    assert!(is_reachable(wall_segments, a), "{:?} isn't reachable", a);
    assert!(is_reachable(wall_segments, b), "{:?} isn't reachable", b);

    wall_segments.iter().all(|&(p, q)| {
        // if !Crd::segments_intersection(a, b, p, q).is_empty() {
        //     eprintln!("{:?} intersects {:?}", (a, b), (p, q));
        // }
        Crd::segments_intersection(a, b, p, q).is_empty()
    })
}

fn reachable_neighs(wall_segments: &[(Crd, Crd)], a: Crd) -> Vec<Crd> {
    a.neighs()
        .into_iter()
        .filter(|&p| is_reachable(wall_segments, p))
        .collect()
}

fn adjacent(wall_segments: &[(Crd, Crd)], finish: Crd, a: Crd) -> Vec<Crd> {
    let mut result: Vec<Crd> = if a == Crd(0, 0) {
        reachable_neighs(wall_segments, a)
    } else {
        vec![]
    };

    if is_b_reachable_from_a(wall_segments, a, finish) {
        result.push(finish);
    }

    let reachable_edge_neighs: Vec<Crd> = wall_segments
        .iter()
        .flat_map(|&(p, q)| vec![p, q])
        .chain(once(finish))
        .flat_map(|p| p.neighs())
        .unique()
        .filter(|&b| is_reachable(wall_segments, b) && is_b_reachable_from_a(wall_segments, a, b))
        .collect();
    result.extend(reachable_edge_neighs);

    // eprintln!("Adjacent to {:?}: {:?}", a, result);
    result
}

fn edges_from(a: Crd, bs: Vec<Crd>) -> Vec<(Crd, u64)> {
    bs.into_iter()
        .map(|b| (b, a.manhattan_distance(b)))
        .collect()
}

fn shortest_path_length(wall_segments: Vec<(Crd, Crd)>, start: Crd, finish: Crd) -> u64 {
    astar(
        &start,
        |&u| edges_from(u, adjacent(&wall_segments, finish, u)),
        |u| u.manhattan_distance(finish),
        |u| *u == finish,
    )
    .unwrap()
    .1
}

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();
    let instructions: Vec<Instr> = buf.trim().split(',').map(Instr::decode).collect();
    let instructions_count = instructions.len();

    let start = Crd(0, 0);
    let mut finish = start;
    let mut wall_segments: Vec<(Crd, Crd)> = vec![];
    let mut crd = Crd(0, 0);
    let mut dir = Dir::N;

    for (i, instr) in instructions.into_iter().enumerate() {
        let k = match instr {
            Instr::L(kk) => {
                dir = dir.turn_left();
                kk
            }
            Instr::R(kk) => {
                dir = dir.turn_right();
                kk
            }
        };

        let next_crd = crd
            + dir
                .delta()
                .mul_by(k - if i == instructions_count - 1 { 1 } else { 0 });

        finish = crd + dir.delta().mul_by(k);
        if crd == Crd(0, 0) {
            crd = crd + dir.delta();
        }
        wall_segments.push((crd, next_crd));
        crd = next_crd;
    }
    // eprintln!("{:?} {:?} → {:?}", wall_segments, start, finish);

    println!("{}", shortest_path_length(wall_segments, start, finish));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_crd_neighs() {
        assert_eq!(
            Crd(0, 0).neighs(),
            vec![
                Crd(-1, 1),
                Crd(1, 1),
                Crd(1, -1),
                Crd(-1, -1),
                Crd(-1, 0),
                Crd(0, 1),
                Crd(1, 0),
                Crd(0, -1)
            ]
        );
    }

    #[test]
    fn test_segments_intersection_a() {
        assert_eq!(
            Crd::segments_intersection(Crd(0, 0), Crd(0, 10), Crd(1, 0), Crd(1, 5)).len(),
            0
        )
    }

    #[test]
    fn test_segments_intersection_b() {
        assert_eq!(
            Crd::segments_intersection(Crd(0, 3), Crd(20, 3), Crd(3, 0), Crd(7, 7)).len(),
            1
        )
    }
}
