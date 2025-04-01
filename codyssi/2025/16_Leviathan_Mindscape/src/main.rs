use std::io::{BufRead, stdin};

#[derive(Clone, Copy, Debug)]
enum Subj {
    Face,
    Row(usize),
    Col(usize),
}

impl Subj {
    fn decode(s: &str) -> Self {
        if s == "FACE" {
            Self::Face
        } else {
            let ab: Vec<_> = s.split_whitespace().collect();
            let i: usize = ab[1].parse().unwrap();
            match ab[0] {
                "ROW" => Self::Row(i),
                "COL" => Self::Col(i),
                _ => panic!("Invalid Subj source `{}`", s),
            }
        }
    }
}

#[derive(Clone, Copy, Debug)]
struct Mutation {
    subj: Subj,
    to_add: u8,
}

impl Mutation {
    fn decode(s: &str) -> Self {
        let ab: Vec<_> = s.split(" - VALUE ").collect();
        let subj = Subj::decode(ab[0]);
        let to_add: u8 = ab[1].parse().unwrap();
        Self { subj, to_add }
    }
}

#[derive(Clone, Copy, Debug)]
enum Rotation {
    U,
    R,
    D,
    L,
}

impl Rotation {
    fn decode(c: char) -> Self {
        match c {
            'U' => Self::U,
            'R' => Self::R,
            'D' => Self::D,
            'L' => Self::L,
            _ => panic!("Invalid rotation source `{}`", c),
        }
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let isep = lines.iter().position(|s| s.is_empty()).unwrap();

    let mutations: Vec<Mutation> = lines[..isep].iter().map(|s| Mutation::decode(s)).collect();
    eprintln!("{:?}", mutations);

    let roations: Vec<Rotation> = lines[isep + 1].chars().map(Rotation::decode).collect();
    eprintln!("{:?}", roations);
}
