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
            (NumKey::A, NumKey::N0) => vec![vec![Dir::W]],
            (NumKey::A, NumKey::N1) => {
                vec![vec![Dir::N, Dir::W, Dir::W], vec![Dir::W, Dir::N, Dir::W]]
            }
            (NumKey::A, NumKey::N2) => unique_permutations(&[Dir::N, Dir::W]),
            (NumKey::A, NumKey::N3) => vec![vec![Dir::N]],
            (NumKey::A, NumKey::N4) => [
                vec![
                    vec![Dir::N, Dir::W, Dir::W, Dir::N],
                    vec![Dir::W, Dir::N, Dir::W, Dir::N],
                ],
                prefix(vec![Dir::N, Dir::W], unique_permutations(&[Dir::N, Dir::W])),
                prefix(vec![Dir::W, Dir::N], unique_permutations(&[Dir::N, Dir::W])),
                preinsert(Dir::N, unique_permutations(&[Dir::N, Dir::W, Dir::W])),
            ]
            .concat(),
            (NumKey::A, NumKey::N5) => unique_permutations(&[Dir::N, Dir::N, Dir::W]),
            (NumKey::A, NumKey::N6) => vec![vec![Dir::N, Dir::N]],
            (NumKey::A, NumKey::N7) => [
                vec![
                    vec![Dir::N, Dir::W, Dir::W, Dir::N, Dir::N],
                    vec![Dir::W, Dir::N, Dir::W, Dir::N, Dir::N],
                ],
                prefix(
                    vec![Dir::N, Dir::W],
                    unique_permutations(&[Dir::N, Dir::N, Dir::W]),
                ),
                prefix(
                    vec![Dir::W, Dir::N],
                    unique_permutations(&[Dir::N, Dir::N, Dir::W]),
                ),
                preinsert(
                    Dir::N,
                    unique_permutations(&[Dir::N, Dir::N, Dir::W, Dir::W]),
                ),
            ]
            .concat(),
            (NumKey::A, NumKey::N8) => unique_permutations(&[Dir::N, Dir::N, Dir::N, Dir::W]),
            (NumKey::A, NumKey::N9) => vec![vec![Dir::N, Dir::N, Dir::N]],
            (NumKey::A, NumKey::A) => vec![],

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

            (NumKey::N1, NumKey::N0) => vec![vec![Dir::E, Dir::S]],
            (NumKey::N1, NumKey::N1) => vec![],
            (NumKey::N1, NumKey::N2) => vec![vec![Dir::E]],
            (NumKey::N1, NumKey::N3) => unique_permutations(&[Dir::E, Dir::E]),
            (NumKey::N1, NumKey::N4) => vec![vec![Dir::N]],
            (NumKey::N1, NumKey::N5) => unique_permutations(&[Dir::N, Dir::E]),
            (NumKey::N1, NumKey::N6) => unique_permutations(&[Dir::N, Dir::E, Dir::E]),
            (NumKey::N1, NumKey::N7) => vec![vec![Dir::N, Dir::N]],
            (NumKey::N1, NumKey::N8) => unique_permutations(&[Dir::N, Dir::N, Dir::E]),
            (NumKey::N1, NumKey::N9) => unique_permutations(&[Dir::N, Dir::N, Dir::E, Dir::E]),
            (NumKey::N1, NumKey::A) => preinsert(Dir::E, unique_permutations(&[Dir::S, Dir::E])),

            (NumKey::N2, NumKey::N0) => vec![vec![Dir::S]],
            (NumKey::N2, NumKey::N1) => vec![vec![Dir::W]],
            (NumKey::N2, NumKey::N2) => vec![],
            (NumKey::N2, NumKey::N3) => vec![vec![Dir::E]],
            (NumKey::N2, NumKey::N4) => unique_permutations(&[Dir::N, Dir::W]),
            (NumKey::N2, NumKey::N5) => vec![vec![Dir::N]],
            (NumKey::N2, NumKey::N6) => unique_permutations(&[Dir::N, Dir::E]),
            (NumKey::N2, NumKey::N7) => unique_permutations(&[Dir::N, Dir::N, Dir::W]),
            (NumKey::N2, NumKey::N8) => vec![vec![Dir::N, Dir::N]],
            (NumKey::N2, NumKey::N9) => unique_permutations(&[Dir::N, Dir::N, Dir::E]),
            (NumKey::N2, NumKey::A) => unique_permutations(&[Dir::S, Dir::E]),

            (NumKey::N3, NumKey::N0) => unique_permutations(&[Dir::S, Dir::W]),
            (NumKey::N3, NumKey::N1) => vec![vec![Dir::W, Dir::W]],
            (NumKey::N3, NumKey::N2) => vec![vec![Dir::W]],
            (NumKey::N3, NumKey::N3) => vec![],
            (NumKey::N3, NumKey::N4) => unique_permutations(&[Dir::N, Dir::W, Dir::W]),
            (NumKey::N3, NumKey::N5) => unique_permutations(&[Dir::N, Dir::W]),
            (NumKey::N3, NumKey::N6) => vec![vec![Dir::N]],
            (NumKey::N3, NumKey::N7) => unique_permutations(&[Dir::N, Dir::N, Dir::W, Dir::W]),
            (NumKey::N3, NumKey::N8) => unique_permutations(&[Dir::N, Dir::N, Dir::W]),
            (NumKey::N3, NumKey::N9) => vec![vec![Dir::N, Dir::N]],
            (NumKey::N3, NumKey::A) => vec![vec![Dir::S]],

            _ => todo!(),
        }
    }
}

fn append<T>(mut xss: Vec<T>, ys: T) -> Vec<T> {
    xss.push(ys);
    xss
}

fn preinsert<T: Clone>(with: T, mut xss: Vec<Vec<T>>) -> Vec<Vec<T>> {
    xss.iter_mut().for_each(|xs| xs.insert(0, with.clone()));
    xss
}

fn prefix<T: Clone>(with: Vec<T>, xss: Vec<Vec<T>>) -> Vec<Vec<T>> {
    xss.into_iter()
        .map(|xs| {
            let mut ys = with.clone();
            ys.extend(xs);
            ys
        })
        .collect()
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
