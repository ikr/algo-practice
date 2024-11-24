use std::{
    collections::HashSet,
    io::{self, BufRead},
};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i16, i16);

impl Crd {
    fn mul_by(self, scalar: i16) -> Crd {
        Crd(self.0 * scalar, self.1 * scalar)
    }
}

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
    fn delta(&self) -> Crd {
        match self {
            Dir::N => Crd(-1, 0),
            Dir::E => Crd(0, 1),
            Dir::S => Crd(1, 0),
            Dir::W => Crd(0, -1),
        }
    }
}

struct Grid {
    rows: Vec<Vec<u8>>,
}

impl Grid {
    fn height(&self) -> usize {
        self.rows.len()
    }

    fn width(&self) -> usize {
        assert!(!self.rows.is_empty());
        self.rows[0].len()
    }
}

fn reversed<T: Clone>(s: &[T]) -> Vec<T> {
    let mut xs = s.to_vec();
    xs.reverse();
    xs
}

fn code_of(xs: &[u8]) -> u64 {
    (0..xs.len() as u32)
        .rev()
        .map(|e| 27u64.pow(e))
        .into_iter()
        .zip(xs)
        .map(|(b, x)| b * (x - b'@') as u64)
        .sum()
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap())
        .collect();

    let words: Vec<String> = lines[0]
        .strip_prefix("WORDS:")
        .unwrap()
        .split(',')
        .map(|s| s.trim().to_string())
        .collect();

    let max_word_length = words.iter().map(|s| s.len()).max().unwrap();
    dbg!(max_word_length);

    let grid: Vec<Vec<u8>> = lines[2..]
        .iter()
        .map(|line| line.as_bytes().iter().cloned().collect())
        .collect();
}
