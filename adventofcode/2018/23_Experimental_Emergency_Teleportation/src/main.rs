use regex::Regex;
use std::cmp;
use std::io::{self, BufRead};

type Xyz = [i32; 3];
type Ijkl = [i32; 4];
type Pii = (i32, i32);

fn modified_at(mut xyz: Xyz, i: usize, value: i32) -> Xyz {
    xyz[i] = value;
    xyz
}

fn intersection(ab: Pii, cd: Pii) -> Option<Pii> {
    let (a, b) = ab;
    assert!(a <= b);
    let (c, d) = cd;
    assert!(c <= d);

    if a > d || c > b {
        None
    } else {
        Some((cmp::max(a, c), cmp::min(b, d)))
    }
}

fn manhattan(one: &Xyz, two: &Xyz) -> i32 {
    let mut result: i32 = 0;
    for (i, a) in one.iter().enumerate() {
        result += (a - two[i]).abs();
    }
    result
}

fn chebyshev(one: &Ijkl, two: &Ijkl) -> i32 {
    let mut result: i32 = 0;
    for (i, a) in one.iter().enumerate() {
        result = cmp::max(result, (a - two[i]).abs());
    }
    result
}

fn rotate_45(xs: &Xyz) -> Ijkl {
    [
        xs[0] + xs[1] + xs[2],
        xs[0] + xs[1] - xs[2],
        xs[0] - xs[1] + xs[2],
        xs[0] - xs[1] - xs[2],
    ]
}

fn inof(src: &str) -> i32 {
    src.parse().unwrap()
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

    fn in_range(&self, a: &Xyz) -> bool {
        manhattan(&self.position, a) <= self.signal_radius
    }

    fn overlaps_with(&self, o: &Bot) -> bool {
        manhattan(&self.position, &o.position) <= self.signal_radius + o.signal_radius
    }

    fn contains(&self, o: &Bot) -> bool {
        let mut vertices: Vec<Xyz> = Vec::new();
        for (i, a) in o.position.iter().enumerate() {
            vertices.push(modified_at(o.position, i, a - o.signal_radius));
            vertices.push(modified_at(o.position, i, a + o.signal_radius));
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

fn out_degrees(g: &[Vec<usize>]) -> Vec<u16> {
    let n = g.len();
    let mut result: Vec<u16> = vec![0; n];
    for i in 0..n {
        result[i] = g[i].len() as u16;
    }
    result
}

fn eprint_graph_stats(g: &[Vec<usize>]) {
    let n = g.len();
    let deg = out_degrees(g);
    let mut dis: Vec<(u16, usize)> = (0..n).map(|i| (deg[i], i)).collect();
    dis.sort();
    eprintln!("top-deg: {:?}", &dis[n - 6..n]);
}

fn solve_part_2(bots: &[Bot]) {
    eprint_graph_stats(&overlap_graph(bots));
    let g = containment_graph(bots);
    eprint_graph_stats(&g);

    let n = g.len();
    let deg = out_degrees(&g);
    let mut dis: Vec<(u16, usize)> = (0..n).map(|i| (deg[i], i)).collect();
    dis.sort();

    for (m, u0) in dis.iter() {
        eprintln!("{} has an out-deg of {}", u0, m);
        if *m == 0 {
            continue;
        }

        for i in 0..*m - 1 {
            for j in i + 1..*m {
                let u = g[*u0][i as usize];
                let v = g[*u0][j as usize];
                if !bots[u].overlaps_with(&bots[v]) {
                    eprintln!("{} and {} don't overlap", u, v);
                }
            }
        }
    }

    let (_, u) = dis.last().unwrap();
    for v in 0..n {
        if *u == v || g[*u].contains(&v) {
            continue;
        }

        for w in g[*u].iter() {
            if bots[v].overlaps_with(&bots[*w]) {
                eprintln!("{} overlaps with {}", w, v);
            }
        }
    }
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
