use std::io::{self, BufRead};

const AZ: u16 = 26;

struct Wire {
    code: u16,
}

impl Wire {
    fn ordinal(lowercase_letter: u8) -> u16 {
        (lowercase_letter - b'a').into()
    }

    fn from_id(id: &str) -> Wire {
        let code: u16 = match id.as_bytes() {
            [y] => Wire::ordinal(*y),
            [x, y] => AZ * Wire::ordinal(*x) + Wire::ordinal(*y),
            _ => panic!("{} is neither a single char nor a pair", id),
        };
        Wire { code }
    }
}

struct Signal(u16);

impl Signal {
    fn parse(src: &str) -> Signal {
        Signal(src.parse().unwrap())
    }
}

enum Lval {
    Wire(Wire),
    Signal(Signal),
}

impl Lval {
    fn value(&self, env: &[u16]) -> u16 {
        assert!(env.len() >= (AZ * AZ).into());
        match &self {
            Lval::Wire(Wire { code }) => env[*code as usize],
            Lval::Signal(Signal(constant_value)) => *constant_value,
        }
    }
}

enum Op {
    Imm(Lval),
    Not(Wire),
    Lshift(Wire, Signal),
    Rshift(Wire, Signal),
    And(Lval, Lval),
    Or(Lval, Lval),
}

fn main() {
    let grid: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();
}
