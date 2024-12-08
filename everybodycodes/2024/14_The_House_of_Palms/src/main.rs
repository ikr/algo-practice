use std::{
    collections::{HashMap, HashSet, VecDeque},
    io::{self, BufRead},
};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i32, i32, i32);

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1, self.2 + o.2)
    }
}

#[derive(Clone, Copy, Debug)]
enum Dir {
    U,
    D,
    L,
    R,
    F,
    B,
}

impl Dir {
    fn new(src: char) -> Dir {
        match src {
            'U' => Dir::U,
            'D' => Dir::D,
            'L' => Dir::L,
            'R' => Dir::R,
            'F' => Dir::F,
            'B' => Dir::B,
            _ => panic!("Invalid direction {}", src),
        }
    }

    fn delta(&self) -> Crd {
        match self {
            Dir::U => Crd(0, 0, 1),
            Dir::D => Crd(0, 0, -1),
            Dir::L => Crd(-1, 0, 0),
            Dir::R => Crd(1, 0, 0),
            Dir::F => Crd(0, 1, 0),
            Dir::B => Crd(0, -1, 0),
        }
    }

    fn all() -> Vec<Dir> {
        vec![Dir::U, Dir::D, Dir::L, Dir::R, Dir::F, Dir::B]
    }
}

fn parse_command(s: &str) -> (Dir, u32) {
    let chars = s.chars().collect::<Vec<_>>();
    (
        Dir::new(chars[0]),
        chars[1..].iter().collect::<String>().parse().unwrap(),
    )
}

fn total_distance_to(segs: &HashSet<Crd>, source: Crd, dests: &[Crd]) -> u32 {
    let mut distances: HashMap<Crd, u32> = HashMap::new();
    distances.insert(source, 0);

    let mut q: VecDeque<Crd> = VecDeque::new();
    q.push_back(source);

    while let Some(u) = q.pop_front() {
        for dir in Dir::all() {
            let v = u + dir.delta();
            if segs.contains(&v) && !distances.contains_key(&v) {
                distances.insert(v, distances[&u] + 1);
                q.push_back(v);
            }
        }
    }

    dests.iter().map(|d| distances[d]).sum()
}

fn trunk(segs: &HashSet<Crd>) -> Vec<Crd> {
    let mut result = vec![Dir::U.delta()];

    while segs.contains(&(*result.last().unwrap() + Dir::U.delta())) {
        result.push(*result.last().unwrap() + Dir::U.delta());
    }

    result
}

fn main() {
    let command_lines = io::stdin()
        .lock()
        .lines()
        .map(|line| {
            line.unwrap()
                .split(',')
                .map(parse_command)
                .collect::<Vec<_>>()
        })
        .collect::<Vec<_>>();

    let mut segs: HashSet<Crd> = HashSet::new();
    let mut leaves: Vec<Crd> = vec![];

    for commands in command_lines {
        let mut cur = Crd(0, 0, 0);

        for (dir, l) in commands {
            for _ in 0..l {
                cur = cur + dir.delta();
                segs.insert(cur);
            }
        }

        leaves.push(cur);
    }

    let result = trunk(&segs)
        .into_iter()
        .map(|source| total_distance_to(&segs, source, &leaves))
        .min()
        .unwrap();
    println!("{}", result);
}
