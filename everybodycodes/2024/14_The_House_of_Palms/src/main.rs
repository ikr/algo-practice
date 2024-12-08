use std::{
    collections::HashSet,
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
    fn new(src: char) -> Self {
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
}

fn parse_command(s: &str) -> (Dir, u32) {
    let chars = s.chars().collect::<Vec<_>>();
    (
        Dir::new(chars[0]),
        chars[1..].iter().collect::<String>().parse().unwrap(),
    )
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

    for commands in command_lines {
        let mut cur = Crd(0, 0, 0);

        for (dir, l) in commands {
            for _ in 0..l {
                cur = cur + dir.delta();
                segs.insert(cur);
            }
        }
    }

    println!("{}", segs.len());
}
