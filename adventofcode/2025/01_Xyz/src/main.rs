use std::io::{BufRead, stdin};

const M: i32 = 100;

#[derive(Clone, Copy, Debug)]
enum Instr {
    L(i32),
    R(i32),
}

impl Instr {
    fn decode(s: &str) -> Self {
        let x: i32 = s[1..].parse().unwrap();

        match s.bytes().next().unwrap() {
            b'L' => Self::L(x),
            b'R' => Self::R(x),
            _ => unreachable!(),
        }
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let instrs: Vec<Instr> = lines.into_iter().map(|s| Instr::decode(&s)).collect();

    let mut result = 0;
    let mut cur: i32 = 50;

    for instr in instrs {
        match instr {
            Instr::L(x) => cur -= x,
            Instr::R(x) => cur += x,
        }

        cur %= M;
        cur += M;
        cur %= M;
        if cur == 0 {
            result += 1;
        }
    }

    println!("{result}");
}
