use std::io::{self, BufRead};

use regex::Regex;

const H: i32 = 103;
const W: i32 = 101;
// const H: i32 = 7;
// const W: i32 = 11;

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i32, i32);

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

struct Robot {
    position: Crd,
    velocity: Crd,
}

impl Robot {
    fn new(position: Crd, velocity: Crd) -> Robot {
        Robot { position, velocity }
    }

    fn tick(&self) -> Robot {
        let Crd(x0, y0) = self.position + self.velocity;
        let x = (x0 + 10 * W) % W;
        let y = (y0 + 10 * H) % H;

        Robot {
            position: Crd(x, y),
            velocity: self.velocity,
        }
    }
}

fn parse_point_and_velocity(s: &str) -> (Crd, Crd) {
    let re = Regex::new(r"^p=(\d+),(\d+) v=(-?\d+),(-?\d+)$").unwrap();
    let caps = re.captures(s).unwrap();
    (
        Crd(caps[1].parse().unwrap(), caps[2].parse().unwrap()),
        Crd(caps[3].parse().unwrap(), caps[4].parse().unwrap()),
    )
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().to_string())
        .collect();

    let points_and_velocities: Vec<(Crd, Crd)> =
        lines.iter().map(|s| parse_point_and_velocity(s)).collect();

    let mut robots: Vec<Robot> = points_and_velocities
        .iter()
        .map(|(p, v)| Robot::new(*p, *v))
        .collect();

    for _ in 0..100 {
        for robot in robots.iter_mut() {
            *robot = robot.tick();
        }
    }

    let mut quadrants = [0 as usize; 4];

    for robot in robots.iter() {
        let Crd(x, y) = robot.position;
        if x < W / 2 && y < H / 2 {
            quadrants[0] += 1;
        } else if x > W / 2 && y < H / 2 {
            quadrants[1] += 1;
        } else if x < W / 2 && y > H / 2 {
            quadrants[2] += 1;
        } else if x > W / 2 && y > H / 2 {
            quadrants[3] += 1;
        }
    }

    eprintln!("{:?}", quadrants);

    let result: usize = quadrants.iter().product();
    println!("{}", result);
}
