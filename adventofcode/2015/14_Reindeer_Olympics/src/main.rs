use regex::Regex;
use std::io::{self, BufRead};

#[derive(Debug)]
struct Mobility {
    velocity: i64,
    flight_seconds: i64,
    rest_seconds: i64,
}

impl Mobility {
    fn distance(&self, t: i64) -> i64 {
        let p = self.flight_seconds + self.rest_seconds;
        let full_cycles = t / p;
        let cycle_distance = self.velocity * self.flight_seconds;
        let r = (t % p).min(self.flight_seconds);
        full_cycles * cycle_distance + self.velocity * r
    }
}

fn parse_fact(src: &str) -> (String, Mobility) {
    let re = Regex::new(r"^([A-Z][a-z]+) can fly (\d+) km/s for (\d+) seconds, but then must rest for (\d+) seconds.$").unwrap();
    let caps = re.captures(src).unwrap();
    let velocity = caps[2].parse().unwrap();
    let flight_seconds = caps[3].parse().unwrap();
    let rest_seconds = caps[4].parse().unwrap();
    (
        caps[1].to_string(),
        Mobility {
            velocity,
            flight_seconds,
            rest_seconds,
        },
    )
}

fn main() {
    let facts: Vec<_> = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_fact(&line.unwrap()))
        .collect();

    let t = 2503;
    let ds: Vec<_> = facts.into_iter().map(|(_, mob)| mob.distance(t)).collect();
    println!("{}", ds.into_iter().max().unwrap());
}
