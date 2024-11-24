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

    fn interval_right(&self, length: i16) -> Vec<Crd> {
        (0..length).map(|i| *self + Crd(0, i)).collect()
    }

    fn interval_down(&self, length: i16) -> Vec<Crd> {
        (0..length).map(|i| *self + Crd(i, 0)).collect()
    }

    fn all_containing_horizontal_intervals(&self, exact_interval_length: i16) -> Vec<Vec<Crd>> {
        let mut cur = self.interval_right(exact_interval_length);
        let mut result: Vec<Vec<Crd>> = vec![cur.clone()];

        for _ in 1..exact_interval_length {
            cur = shift_left(cur);
            result.push(cur.clone());
        }

        result
    }

    fn all_containing_vertical_intervals(&self, exact_interval_length: i16) -> Vec<Vec<Crd>> {
        let mut cur = self.interval_down(exact_interval_length);
        let mut result: Vec<Vec<Crd>> = vec![cur.clone()];

        for _ in 1..exact_interval_length {
            cur = shift_up(cur);
            result.push(cur.clone());
        }

        result
    }
}

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

fn shift_up(mut crds: Vec<Crd>) -> Vec<Crd> {
    crds.iter_mut().for_each(|Crd(ro, _)| *ro -= 1);
    crds
}

fn shift_left(mut crds: Vec<Crd>) -> Vec<Crd> {
    crds.iter_mut().for_each(|Crd(_, co)| *co -= 1);
    crds
}

struct Grid {
    rows: Vec<Vec<u8>>,
}

impl Grid {
    fn height(&self) -> i16 {
        self.rows.len() as i16
    }

    fn width(&self) -> i16 {
        assert!(!self.rows.is_empty());
        self.rows[0].len() as i16
    }

    fn cell(&self, crd: Crd) -> u8 {
        let n = self.height();
        let m = self.width();
        let ro = (crd.0 + n) % n;
        let co = (crd.1 + m) % m;
        self.rows[ro as usize][co as usize]
    }

    fn interval(&self, crds: &[Crd]) -> Vec<u8> {
        crds.iter().map(|&crd| self.cell(crd)).collect()
    }
}

fn reversed<T: Clone>(s: &[T]) -> Vec<T> {
    let mut xs = s.to_vec();
    xs.reverse();
    xs
}

fn all_reversed<T: Clone>(s: &[Vec<T>]) -> Vec<Vec<T>> {
    s.iter().map(|xs| reversed(xs)).collect()
}

fn code_of(xs: &[u8]) -> u64 {
    (0..xs.len() as u32)
        .rev()
        .map(|e| 27u64.pow(e))
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

    let word_lengths = words.iter().map(|s| s.len()).collect::<Vec<_>>();
    let min_word_length = word_lengths.iter().min().unwrap();
    let max_word_length = word_lengths.iter().max().unwrap();

    let grid_rows: Vec<Vec<u8>> = lines[2..]
        .iter()
        .map(|line| line.as_bytes().to_vec())
        .collect();

    let grid = Grid { rows: grid_rows };
}
