use std::io::{BufRead, stdin};

#[derive(Clone, Copy, Debug)]
enum Subj {
    Face,
    Row(usize),
    Col(usize),
}

impl Subj {
    fn parse(s: &str) -> Self {
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

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let isep = lines.iter().position(|s| s.is_empty()).unwrap();
    eprintln!("{:?}", lines);
}
