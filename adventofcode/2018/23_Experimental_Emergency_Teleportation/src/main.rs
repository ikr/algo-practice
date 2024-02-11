use regex::Regex;
use std::io::{self, BufRead};

type Xyz = [i32; 3];

fn inof(src: &str) -> i32 {
    src.parse().unwrap()
}

fn modified_at(mut xyz: Xyz, i: usize, value: i32) -> Xyz {
    xyz[i] = value;
    xyz
}

#[derive(Clone, Copy)]
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

    fn overlaps_with(&self, o: &Bot) -> bool {
        self.distance(&o.position) <= self.signal_radius + o.signal_radius
    }

    fn contains(&self, o: &Bot) -> bool {
        let mut vertices: Vec<Xyz> = Vec::new();
        for i in 0..3 {
            vertices.push(modified_at(o.position, i, o.position[i] - o.signal_radius));
            vertices.push(modified_at(o.position, i, o.position[i] + o.signal_radius));
        }
        vertices.iter().all(|&u| self.in_range(&u))
    }
}

fn solve_part_1(bots: &[Bot]) {
    let a: &Bot = bots.last().unwrap();
    let result = bots.iter().filter(|b| a.in_range(&b.position)).count();
    println!("{}", result);
}

fn graph<F>(bots: &[Bot], adj: F) -> Vec<Vec<usize>>
where
    F: Fn(&Bot, &Bot) -> bool,
{
    let n = bots.len();
    let mut result: Vec<Vec<usize>> = vec![vec![]; n];
    for i in 0..n - 1 {
        for j in i + 1..n {
            if adj(&bots[i], &bots[j]) {
                result[i].push(j);
            }
            if adj(&bots[j], &bots[i]) {
                result[j].push(i);
            }
        }
    }
    result
}

fn overlap_graph(bots: &[Bot]) -> Vec<Vec<usize>> {
    graph(bots, |a, b| a.overlaps_with(b))
}

fn containment_graph(bots: &[Bot]) -> Vec<Vec<usize>> {
    graph(bots, |a, b| a.contains(b))
}

fn solve_part_2(bots: &[Bot]) {
    eprintln!("Number of bots: {}", bots.len());
    eprintln!("{:?}", overlap_graph(&bots));
    eprintln!("{:?}", containment_graph(&bots));
}

fn main() {
    let bots: Vec<Bot> = io::stdin()
        .lock()
        .lines()
        .map(|l| Bot::parse(&l.unwrap()))
        .collect();

    let mut bots_sorted: Vec<Bot> = bots.clone();
    bots_sorted.sort_by_key(|b| b.signal_radius);
    solve_part_1(&bots_sorted);

    solve_part_2(&bots);
}
