use std::io::Read;

#[derive(Clone, Copy, Debug)]
enum Instr {
    L(i32),
    R(i32),
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

impl Crd {
    fn scale_by(self, k: i32) -> Self {
        Self(k * self.0, k * self.1)
    }

    fn dot(self, p: Self) -> i32 {
        self.0 * p.0 + self.1 * p.1
    }

    fn cross(self, p: Self) -> i32 {
        self.0 * p.1 - self.1 * p.0
    }

    fn cross_ab(self, a: Self, b: Self) -> i32 {
        (a - self).cross(b - self)
    }

    fn on_segment(s: Self, e: Self, p: Self) -> bool {
        p.cross_ab(s, e) == 0 && (s - p).dot(e - p) <= 0
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

fn shortest_path_length(wall_segments: Vec<(Crd, Crd)>, start: Crd, finish: Crd) -> u32 {
    eprintln!("{:?} {:?} → {:?}", wall_segments, start, finish);
    todo!()
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
                .scale_by(k - if i == instructions_count - 1 { 1 } else { 0 });

        finish = crd + dir.delta().scale_by(k);
        wall_segments.push((crd, next_crd));
        crd = next_crd;
    }

    println!("{}", shortest_path_length(wall_segments, start, finish));
}
