use std::io::{BufRead, stdin};

#[derive(Clone, Copy, Debug)]
enum Op {
    L(usize),
    R(usize),
}

impl Op {
    fn decode(s: &str) -> Self {
        let k: usize = s[1..].parse().unwrap();
        match s.chars().next().unwrap() {
            'L' => Self::L(k),
            'R' => Self::R(k),
            _ => unreachable!(),
        }
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let names: Vec<String> = lines[0].split(',').map(|x| x.to_string()).collect();
    let ops: Vec<Op> = lines[2].split(',').map(Op::decode).collect();
    let n = names.len();

    let i = ops.into_iter().fold(0usize, |acc, op| match op {
        Op::L(k) => acc.saturating_sub(k),
        Op::R(k) => (n - 1).min(acc + k),
    });
    println!("{}", names[i]);
}
