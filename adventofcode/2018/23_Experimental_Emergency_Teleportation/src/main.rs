use regex::Regex;
use std::io::{self, BufRead};

type Xyz = [i32; 3];

fn inof(src: &str) -> i32 {
    src.parse().unwrap()
}

#[derive(Debug)]
struct Bot {
    position: Xyz,
    signal_radius: i32,
}

impl Bot {
    fn parse(src: &str) -> Bot {
        let re = Regex::new(r"^pos=<(-?\d+),(-?\d+),(-?\d+)>, r=(\d+)$").unwrap();
        let caps = re.captures(src).unwrap();
        Bot {
            position: [inof(&caps[1]), inof(&caps[2]), inof(&caps[3])],
            signal_radius: inof(&caps[4]),
        }
    }

    fn distance(&self, a: &Xyz) -> i32 {
        let mut result: i32 = 0;
        for i in 0..3 {
            result += (self.position[i] - a[i]).abs();
        }
        result
    }

    fn in_range(&self, a: &Xyz) -> bool {
        self.distance(a) <= self.signal_radius
    }

    fn adjacent(&self, o: &Bot) -> bool {
        self.distance(&o.position) <= self.signal_radius + o.signal_radius
    }
}

fn solve_part_1(bots: &[Bot]) {
    let a: &Bot = bots.last().unwrap();
    let result = bots.iter().filter(|b| a.in_range(&b.position)).count();
    println!("{}", result);
}

fn adjacency_list(bots: &[Bot]) -> Vec<Vec<usize>> {
    let n = bots.len();
    let mut result: Vec<Vec<usize>> = vec![vec![]; n];
    for i in 0..n - 1 {
        for j in i + 1..n {
            if bots[i].adjacent(&bots[j]) {
                result[i].push(j);
                result[j].push(i);
            }
        }
    }
    result
}

fn solve_part_2(bots: &[Bot]) {
    eprintln!("Number of bots: {}", bots.len());
    eprint!("{:?}", adjacency_list(&bots));
}

fn main() {
    let mut bots: Vec<Bot> = io::stdin()
        .lock()
        .lines()
        .map(|l| Bot::parse(&l.unwrap()))
        .collect();
    bots.sort_by_key(|b| b.signal_radius);
    solve_part_1(&bots);
    solve_part_2(&bots);
}
