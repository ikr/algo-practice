use std::io::{self, BufRead};

const AZ: u16 = 26;

#[derive(Debug)]
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

#[derive(Debug)]
struct Signal(u16);

impl Signal {
    fn parse(src: &str) -> Signal {
        Signal(src.parse().unwrap())
    }
}

#[derive(Debug)]
enum Lval {
    Wire(Wire),
    Signal(Signal),
}

impl Lval {
    fn parse(src: &str) -> Lval {
        if src.as_bytes().first().unwrap().is_ascii_digit() {
            Lval::Signal(Signal::parse(src))
        } else {
            Lval::Wire(Wire::from_id(src))
        }
    }

    fn value(&self, env: &[u16]) -> u16 {
        assert!(env.len() >= (AZ * AZ).into());
        match &self {
            Lval::Wire(Wire { code }) => env[*code as usize],
            Lval::Signal(Signal(constant_value)) => *constant_value,
        }
    }
}

#[derive(Debug)]
enum Op {
    Imm(Lval),
    Not(Lval),
    Lshift(Lval, Lval),
    Rshift(Lval, Lval),
    And(Lval, Lval),
    Or(Lval, Lval),
}

impl Op {
    fn parse_bin_parts(src: &str) -> Option<(Lval, String, Lval)> {
        let parts: Vec<&str> = src.split(' ').collect();
        if let [a, b, c] = parts[..] {
            Some((Lval::parse(a), b.to_owned(), Lval::parse(c)))
        } else {
            None
        }
    }

    fn parse(src: &str) -> Op {
        if let Some(suffix) = src.strip_prefix("NOT ") {
            Op::Not(Lval::parse(suffix))
        } else if let Some((a, b, c)) = Op::parse_bin_parts(src) {
            match b.as_str() {
                "AND" => Op::And(a, c),
                "OR" => Op::Or(a, c),
                "LSHIFT" => Op::Lshift(a, c),
                "RSHIFT" => Op::Rshift(a, c),
                _ => panic!("Invalid binary opcode {}", b),
            }
        } else {
            assert_eq!(src.split(' ').count(), 1);
            Op::Imm(Lval::parse(src))
        }
    }
}

#[derive(Debug)]
struct Instr {
    op: Op,
    out: Wire,
}

impl Instr {
    fn parse(src: &str) -> Instr {
        let parts: Vec<&str> = src.split(" -> ").collect();
        if let [lhs, rhs] = parts[..] {
            Instr {
                op: Op::parse(lhs),
                out: Wire::from_id(rhs),
            }
        } else {
            panic!("Invalid instruction {}", src)
        }
    }
}

fn main() {
    let instructions: Vec<Instr> = io::stdin()
        .lock()
        .lines()
        .map(|line| Instr::parse(&line.unwrap()))
        .collect();
    eprintln!("{:?}", instructions);
}
