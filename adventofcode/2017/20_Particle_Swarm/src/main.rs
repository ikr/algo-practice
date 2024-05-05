use regex::Regex;
use std::io::{self, BufRead};

const END_OF_TIME: i64 = 10_000_000;

fn decode_triple(src: &str) -> [i64; 3] {
    let parts: Vec<String> = src.split(',').map(|x| x.to_string()).collect();
    assert!(parts.len() == 3);
    parts
        .into_iter()
        .map(|s| s.parse::<i64>().unwrap())
        .collect::<Vec<i64>>()
        .try_into()
        .unwrap()
}

fn decode_particle(src: &str) -> Particle {
    let re = Regex::new("^p=<(.+)>, v=<(.+)>, a=<(.+)>$").unwrap();
    let caps = re.captures(src).unwrap();
    let [p, v, a] = caps
        .iter()
        .skip(1)
        .map(|c| decode_triple(c.unwrap().as_str()))
        .collect::<Vec<_>>()[..]
    else {
        panic!("Not enough captured")
    };
    Particle { p, v, a }
}

fn manhattan_distance(a: &[i64], b: &[i64]) -> i64 {
    let n = a.len();
    assert!(b.len() == n);
    (0..n).fold(0, |acc, i| acc + (a[i] - b[i]).abs())
}

#[derive(Clone, Copy)]
struct Particle {
    p: [i64; 3],
    v: [i64; 3],
    a: [i64; 3],
}

impl Particle {
    fn manhattan_distance_from_origin(&self) -> i64 {
        manhattan_distance(&self.p, &[0; 3])
    }

    fn simulate_t_ticks(&self, t: i64) -> Particle {
        let mut result = self.clone();
        for i in 0..3 {
            result.v[i] = self.v[i] + self.a[i] * t;
            // It's not the classic S = vt + ½at² formula! Figured it out empirically.
            result.p[i] = self.p[i] + t * (2 * self.v[i] + self.a[i]) / 2 + (self.a[i] * t * t) / 2;
        }
        result
    }

    fn is_getting_closer_to(&self, other: Particle) -> bool {
        manhattan_distance(&self.p, &other.p)
            > manhattan_distance(&self.simulate_t_ticks(1).p, &other.simulate_t_ticks(1).p)
    }

    fn min_distance_to_other_with_time(&self, other: Particle) -> (i64, i64) {
        assert!(self.p != other.p);
        assert!(self.is_getting_closer_to(other));
        assert!(!self
            .simulate_t_ticks(END_OF_TIME)
            .is_getting_closer_to(other.simulate_t_ticks(END_OF_TIME)));

        let mut l = 0i64;
        let mut r = END_OF_TIME;
        while r - l >= 3 {}
    }

    fn time_to_collision(&self, other: Particle) -> Option<i64> {
        if self.p == other.p {
            Some(0)
        } else {
            if self.is_getting_closer_to(other) {
                let (d, t) = self.min_distance_to_other_with_time(other);
                if d == 0 {
                    Some(t)
                } else {
                    None
                }
            } else {
                None
            }
        }
    }
}

fn index_of_particle_closest_to_origin(ps: &[Particle]) -> usize {
    let lo = ps
        .iter()
        .map(|p| p.manhattan_distance_from_origin())
        .min()
        .unwrap();
    ps.iter()
        .position(|p| p.manhattan_distance_from_origin() == lo)
        .unwrap()
}

fn main() {
    let ps: Vec<Particle> = io::stdin()
        .lock()
        .lines()
        .map(|line| decode_particle(&line.unwrap()))
        .collect();

    let qs: Vec<Particle> = ps.iter().map(|p| p.simulate_t_ticks(1_000)).collect();
    println!("{}", index_of_particle_closest_to_origin(&qs));
}
