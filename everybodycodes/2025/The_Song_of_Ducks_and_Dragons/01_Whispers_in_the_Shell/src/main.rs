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
    let mut names: Vec<String> = lines[0].split(',').map(|x| x.to_string()).collect();
    let ops: Vec<Op> = lines[2].split(',').map(Op::decode).collect();
    let n = names.len();

    for op in ops {
        let j: usize = match op {
            Op::L(k) => (100 * n - k) % n,
            Op::R(k) => k % n,
        };
        names.swap(0, j);
    }
    println!("{}", names[0]);
}
