use std::{
    collections::{HashMap, HashSet, VecDeque},
    io::Read,
};

#[derive(Clone, Copy, Debug)]
enum Instr {
    L(usize),
    R(usize),
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
struct Crd(i32, i32);

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
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

fn shortest_path_length(walls: &HashSet<Crd>, start: Crd, finish: Crd) -> usize {
    let mut dist: HashMap<Crd, usize> = HashMap::from([(start, 0)]);
    let mut q: VecDeque<Crd> = VecDeque::from([start]);

    while let Some(u) = q.pop_front() {
        for dir in Dir::all() {
            let du = dist.get(&u).unwrap();
            let v = u + dir.delta();

            if v == finish {
                return du + 1;
            }

            if !dist.contains_key(&v) && !walls.contains(&v) {
                dist.insert(v, du + 1);
                q.push_back(v);
            }
        }
    }

    unreachable!()
}

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();
    let instructions: Vec<Instr> = buf.trim().split(',').map(Instr::decode).collect();

    let start = Crd(0, 0);
    let mut walls: HashSet<Crd> = HashSet::new();
    let mut crd = Crd(0, 0);
    let mut dir = Dir::N;

    for instr in instructions {
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

        for _ in 0..k {
            crd = crd + dir.delta();
            walls.insert(crd);
        }
    }

    walls.remove(&crd);
    let finish = crd;
    println!("{}", shortest_path_length(&walls, start, finish));
}
