use std::{
    hash::Hash,
    io::{self, BufRead},
};

use itertools::Itertools;

#[derive(Clone, Copy, Debug, Hash, Eq, PartialEq)]
enum Dir {
    N,
    E,
    S,
    W,
}

#[derive(Clone, Copy, Debug, PartialEq)]
enum NumKey {
    N0,
    N1,
    N2,
    N3,
    N4,
    N5,
    N6,
    N7,
    N8,
    N9,
    A,
}

impl NumKey {
    fn parse(c: char) -> Self {
        match c {
            '0' => NumKey::N0,
            '1' => NumKey::N1,
            '2' => NumKey::N2,
            '3' => NumKey::N3,
            '4' => NumKey::N4,
            '5' => NumKey::N5,
            '6' => NumKey::N6,
            '7' => NumKey::N7,
            '8' => NumKey::N8,
            '9' => NumKey::N9,
            'A' => NumKey::A,
            _ => panic!("Invalid numpad key source `{}`", c),
        }
    }

    fn numeric_value(&self) -> usize {
        let os: Vec<char> = ('0'..='9').collect();
        os.into_iter()
            .position(|c| *self == Self::parse(c))
            .unwrap()
    }

    fn transitions(&self, to: NumKey) -> Vec<Vec<Dir>> {
        match (self, to) {
            (NumKey::A, NumKey::A) => vec![],
            (NumKey::A, NumKey::N0) => vec![vec![Dir::W]],
            (NumKey::A, NumKey::N1) => {
                vec![vec![Dir::N, Dir::W, Dir::W], vec![Dir::W, Dir::N, Dir::W]]
            }
            (NumKey::A, NumKey::N2) => unique_permutations(&[Dir::N, Dir::W]),
            (NumKey::A, NumKey::N3) => vec![vec![Dir::N]],
            (NumKey::A, NumKey::N4) => vec![
                vec![Dir::N, Dir::W, Dir::W, Dir::N],
                vec![Dir::W, Dir::N, Dir::W, Dir::N],
                todo!(),
            ],

            (NumKey::N0, NumKey::N0) => vec![],
            (NumKey::N0, NumKey::N1) => vec![vec![Dir::N, Dir::W]],
            (NumKey::N0, NumKey::N2) => vec![vec![Dir::N]],
            (NumKey::N0, NumKey::N3) => unique_permutations(&[Dir::N, Dir::E]),
            (NumKey::N0, NumKey::N4) => {
                vec![vec![Dir::N, Dir::N, Dir::W], vec![Dir::N, Dir::W, Dir::N]]
            }
            (NumKey::N0, NumKey::N5) => vec![vec![Dir::N, Dir::N]],
            (NumKey::N0, NumKey::N6) => unique_permutations(&[Dir::N, Dir::N, Dir::E]),
            (NumKey::N0, NumKey::N7) => append(
                preinsert(Dir::N, unique_permutations(&[Dir::N, Dir::N, Dir::W])),
                vec![Dir::N, Dir::W, Dir::N, Dir::N],
            ),
            (NumKey::N0, NumKey::N8) => vec![vec![Dir::N, Dir::N, Dir::N]],
            (NumKey::N0, NumKey::N9) => unique_permutations(&[Dir::N, Dir::N, Dir::N, Dir::E]),
            (NumKey::N0, NumKey::A) => vec![vec![Dir::E]],

            _ => todo!(),
        }
    }
}

fn append<T>(mut xss: Vec<T>, ys: T) -> Vec<T> {
    xss.push(ys);
    xss
}

fn preinsert<T: Clone>(with: T, mut xss: Vec<Vec<T>>) -> Vec<Vec<T>> {
    xss.iter_mut().for_each(|x| x.insert(0, with.clone()));
    xss
}

fn unique_permutations<T: Clone + Hash + Eq>(xs: &[T]) -> Vec<Vec<T>> {
    let n = xs.len();
    xs.iter().cloned().permutations(n).unique().collect()
}

#[derive(Clone, Copy, Debug)]
enum ArrKey {
    U,
    R,
    D,
    L,
    A,
}

fn parse_numpad_code(s: &str) -> Vec<NumKey> {
    s.chars().map(NumKey::parse).collect()
}

fn numeric_value(nks: &[NumKey]) -> usize {
    nks.iter()
        .filter_map(|&nk| {
            if nk == NumKey::A {
                None
            } else {
                Some(nk.numeric_value())
            }
        })
        .fold(0, |acc, x| acc * 10 + x)
}

fn main() {
    let numpad_codes: Vec<Vec<NumKey>> = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_numpad_code(&line.unwrap()))
        .collect();

    eprintln!("{:?}", unique_permutations(&[1, 1, 2]));

    eprintln!(
        "{:?}",
        numpad_codes
            .iter()
            .map(|xs| numeric_value(xs))
            .collect::<Vec<_>>()
    );
}
