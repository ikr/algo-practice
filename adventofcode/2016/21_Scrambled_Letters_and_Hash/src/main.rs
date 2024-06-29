use std::{
    fmt::Debug,
    io::{self, BufRead},
    process::exit,
};

use itertools::Itertools;

fn extract_pair<T>(prefix: &str, infix: &str, src: &str, map_fn: fn(&str) -> T) -> [T; 2]
where
    T: Debug,
{
    src.strip_prefix(prefix)
        .unwrap()
        .split(infix)
        .map(map_fn)
        .collect::<Vec<_>>()
        .try_into()
        .unwrap()
}

fn parse_usize(src: &str) -> usize {
    src.parse().unwrap()
}

fn parse_letter(src: &str) -> u8 {
    let [x] = src.as_bytes() else {
        panic!("{} isn't a single char", src)
    };
    *x
}

#[derive(Debug)]
enum Op {
    SwpPos(usize, usize),
    SwpLtr(u8, u8),
    RotL(usize),
    RotR(usize),
    Rbop(u8),
    Rev(usize, usize),
    Mov(usize, usize),
}

impl Op {
    fn parse(src: &str) -> Op {
        if src.starts_with("swap p") {
            let [x, y] = extract_pair("swap position ", " with position ", src, parse_usize);
            Op::SwpPos(x, y)
        } else if src.starts_with("swap l") {
            let [x, y] = extract_pair("swap letter ", " with letter ", src, parse_letter);
            Op::SwpLtr(x, y)
        } else if src.starts_with("rotate l") {
            let x = src
                .strip_prefix("rotate left ")
                .map(|s| s.trim_end_matches(|c: char| !c.is_numeric()))
                .map(parse_usize)
                .unwrap();
            Op::RotL(x)
        } else if src.starts_with("rotate r") {
            let x = src
                .strip_prefix("rotate right ")
                .map(|s| s.trim_end_matches(|c: char| !c.is_numeric()))
                .map(parse_usize)
                .unwrap();
            Op::RotR(x)
        } else if src.starts_with("rotate b") {
            let x = src
                .strip_prefix("rotate based on position of letter ")
                .map(parse_letter)
                .unwrap();
            Op::Rbop(x)
        } else if src.starts_with("reverse") {
            let [x, y] = extract_pair("reverse positions ", " through ", src, parse_usize);
            Op::Rev(x, y)
        } else if src.starts_with("move") {
            let [x, y] = extract_pair("move position ", " to position ", src, parse_usize);
            Op::Mov(x, y)
        } else {
            panic!("Invalid Op source {}", src)
        }
    }

    fn apply(&self, mut xs: Vec<u8>) -> Vec<u8> {
        let n: usize = xs.len();
        match self {
            Op::SwpPos(i, j) => {
                xs.swap(*i, *j);
                xs
            }
            Op::SwpLtr(p, q) => {
                let i = xs.iter().position(|x| x == p).unwrap();
                let j = xs.iter().position(|x| x == q).unwrap();
                xs.swap(i, j);
                xs
            }
            Op::RotL(i) => {
                xs.rotate_left(*i);
                xs
            }
            Op::RotR(i) => {
                xs.rotate_right(*i);
                xs
            }
            Op::Rbop(p) => {
                let i = xs.iter().position(|x| x == p).unwrap();
                let steps = if i >= 4 { i + 2 } else { i + 1 };
                xs.rotate_right(steps % n);
                xs
            }
            Op::Rev(i, j) => {
                xs[*i..*j + 1].reverse();
                xs
            }
            Op::Mov(i, j) => {
                let x: u8 = xs[*i];
                xs.remove(*i);
                xs.insert(*j, x);
                xs
            }
        }
    }
}

fn scramble(ops: &[Op], xs: Vec<u8>) -> Vec<u8> {
    ops.iter().fold(xs, |acc, op| op.apply(acc))
}

fn main() {
    let ops: Vec<Op> = io::stdin()
        .lock()
        .lines()
        .map(|line| Op::parse(&line.unwrap()))
        .collect();
    let result = scramble(&ops, "abcdefgh".to_owned().into_bytes());
    println!("{}", String::from_utf8(result).unwrap());

    let target = "fbgdceah".to_owned().into_bytes();
    let xs = "abcdefgh".to_owned().into_bytes();
    for perm in xs.iter().permutations(xs.len()) {
        let ys: Vec<u8> = perm.iter().map(|x| **x).collect();
        if scramble(&ops, ys.clone()) == target {
            println!("{}", String::from_utf8(ys).unwrap());
            exit(0);
        }
    }
}
