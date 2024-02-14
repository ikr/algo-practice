use regex::Regex;
use std::cmp;
use std::io::{self, BufRead};

type Xyz = [i32; 3];
type Ijkl = [i32; 4];
type Seg = (i32, i32);

fn modified_at(mut xyz: Xyz, i: usize, value: i32) -> Xyz {
    xyz[i] = value;
    xyz
}

fn intersection(ab: Seg, cd: Seg) -> Option<Seg> {
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

#[derive(Clone, Copy, Debug)]
struct Seg4d {
    sub: [Seg; 4],
}

impl Seg4d {
    fn intersection(&self, o: &Self) -> Option<Self> {
        let mut sub: [Seg; 4] = [(0, 0); 4];
        for i in 0..sub.len() {
            sub[i] = intersection(self.sub[i], o.sub[i])?;
        }
        Some(Self { sub })
    }

    fn distance_to_origin(&self) -> i32 {
        self.sub
            .iter()
            .map(|(x, y)| cmp::min(x.abs(), y.abs()))
            .reduce(|acc, x| cmp::min(acc, x))
            .unwrap()
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

    fn rotated_seg4d(&self) -> Seg4d {
        Seg4d {
            sub: rotate_45(&self.position)
                .iter()
                .map(|a| (a - self.signal_radius, a + self.signal_radius))
                .collect::<Vec<Seg>>()
                .try_into()
                .unwrap(),
        }
    }
}

fn solve_part_1(bots: &[Bot]) {
    let a: &Bot = bots.last().unwrap();
    let result = bots.iter().filter(|b| a.in_range(&b.position)).count();
    println!("{}", result);
}

fn graph<T, F>(objects: &[T], adj: F) -> Vec<Vec<usize>>
where
    F: Fn(&T, &T) -> bool,
{
    let n = objects.len();
    let mut result: Vec<Vec<usize>> = vec![vec![]; n];
    for i in 0..n - 1 {
        for j in i + 1..n {
            if adj(&objects[i], &objects[j]) {
                result[i].push(j);
            }
            if adj(&objects[j], &objects[i]) {
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

fn segs_overlap_graph(segs: &[Seg4d]) -> Vec<Vec<usize>> {
    graph(segs, |a, b| a.intersection(b).is_some())
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
    let og0 = overlap_graph(bots);
    eprint_graph_stats(&og0);

    let cg = containment_graph(bots);
    eprint_graph_stats(&cg);

    let n = cg.len();
    let cdeg = out_degrees(&cg);
    let mut dis: Vec<(u16, usize)> = (0..n).map(|i| (cdeg[i], i)).collect();
    dis.sort();

    for (m, u0) in dis.iter() {
        eprintln!("{} has an out-deg of {}", u0, m);
        if *m == 0 {
            continue;
        }

        for i in 0..*m - 1 {
            for j in i + 1..*m {
                let u = cg[*u0][i as usize];
                let v = cg[*u0][j as usize];
                if !bots[u].overlaps_with(&bots[v]) {
                    eprintln!("{} and {} don't overlap", u, v);
                }
            }
        }
    }

    let (_, u0) = dis.last().unwrap();

    let segs: Vec<Seg4d> = bots.iter().map(|b| b.rotated_seg4d()).collect();
    let og1 = segs_overlap_graph(&segs);
    assert!(og1 == og0);

    let mut x = cg[*u0]
        .iter()
        .map(|i| segs[*i].clone())
        .reduce(|acc, s| acc.intersection(&s).unwrap())
        .unwrap();
    eprintln!("{:?} → {}", x, x.distance_to_origin());

    for v in segs {
        if let Some(x_) = x.intersection(&v) {
            x = x_;
        }
    }
    eprintln!("{:?} → {}", x, x.distance_to_origin());
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
