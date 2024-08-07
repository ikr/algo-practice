use std::{
    collections::{HashMap, VecDeque},
    io::{self, BufRead},
};

const BASE: u16 = 27;
const M: usize = BASE as usize * BASE as usize;

#[derive(Clone)]
struct Wire {
    code: u16,
}

impl Wire {
    fn ordinal(lowercase_letter: u8) -> u16 {
        (lowercase_letter - b'`').into()
    }

    fn from_id(id: &str) -> Wire {
        let code: u16 = match id.as_bytes() {
            [y] => Wire::ordinal(*y),
            [x, y] => BASE * Wire::ordinal(*x) + Wire::ordinal(*y),
            _ => panic!("{} is neither a single char nor a pair", id),
        };
        Wire { code }
    }
}

#[derive(Clone)]
struct Signal(u16);

impl Signal {
    fn parse(src: &str) -> Signal {
        Signal(src.parse().unwrap())
    }
}

#[derive(Clone)]
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
        match &self {
            Lval::Wire(Wire { code }) => env[*code as usize],
            Lval::Signal(Signal(constant_value)) => *constant_value,
        }
    }
}

#[derive(Clone)]
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

    fn prerequisite_codes(&self) -> Vec<u16> {
        match self {
            Op::Imm(Lval::Wire(Wire { code })) => vec![*code],
            Op::Not(Lval::Wire(Wire { code })) => vec![*code],
            Op::Lshift(Lval::Wire(Wire { code }), Lval::Signal(_)) => vec![*code],
            Op::Lshift(Lval::Signal(_), Lval::Wire(Wire { code })) => vec![*code],
            Op::Lshift(Lval::Wire(Wire { code }), Lval::Wire(Wire { code: a })) => vec![*code, *a],
            Op::Rshift(Lval::Wire(Wire { code }), Lval::Signal(_)) => vec![*code],
            Op::Rshift(Lval::Signal(_), Lval::Wire(Wire { code })) => vec![*code],
            Op::Rshift(Lval::Wire(Wire { code }), Lval::Wire(Wire { code: a })) => vec![*code, *a],
            Op::And(Lval::Wire(Wire { code }), Lval::Signal(_)) => vec![*code],
            Op::And(Lval::Signal(_), Lval::Wire(Wire { code })) => vec![*code],
            Op::And(Lval::Wire(Wire { code }), Lval::Wire(Wire { code: a })) => vec![*code, *a],
            Op::Or(Lval::Wire(Wire { code }), Lval::Signal(_)) => vec![*code],
            Op::Or(Lval::Signal(_), Lval::Wire(Wire { code })) => vec![*code],
            Op::Or(Lval::Wire(Wire { code }), Lval::Wire(Wire { code: a })) => vec![*code, *a],
            _ => vec![],
        }
    }

    fn value(&self, env: &[u16]) -> u16 {
        match &self {
            Op::Imm(x) => x.value(env),
            Op::Not(x) => !x.value(env),
            Op::Lshift(x, y) => x.value(env) << y.value(env),
            Op::Rshift(x, y) => x.value(env) >> y.value(env),
            Op::And(x, y) => x.value(env) & y.value(env),
            Op::Or(x, y) => x.value(env) | y.value(env),
        }
    }
}

#[derive(Clone)]
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

fn compute(instructions: &[Instr], override_b: Option<u16>) -> u16 {
    let mut in_deg = [0; M];
    let mut outputs: Vec<Vec<u16>> = vec![vec![]; M];
    let mut instructions_by_output_wire_code: HashMap<u16, Instr> = HashMap::new();

    for instr in instructions {
        let v = instr.out.code;
        let us = instr.op.prerequisite_codes();
        for u in us.iter() {
            outputs[*u as usize].push(v);
        }
        in_deg[v as usize] += us.len();

        assert!(!instructions_by_output_wire_code.contains_key(&instr.out.code));
        instructions_by_output_wire_code.insert(instr.out.code, instr.clone());
    }

    if let Some(x) = override_b {
        instructions_by_output_wire_code.insert(
            Wire::from_id("b").code,
            Instr {
                op: Op::Imm(Lval::Signal(Signal(x))),
                out: Wire::from_id("b"),
            },
        );
    }

    let mut toposorted_wire_codes: Vec<u16> = vec![];
    let mut q: VecDeque<u16> = VecDeque::new();

    for (i, d) in in_deg.iter().enumerate() {
        if *d == 0 {
            q.push_back(i as u16);
        }
    }

    while let Some(u) = q.pop_front() {
        toposorted_wire_codes.push(u);

        for v in outputs[u as usize].iter() {
            assert!(in_deg[*v as usize] > 0);
            in_deg[*v as usize] -= 1;
            if in_deg[*v as usize] == 0 {
                q.push_back(*v);
            }
        }
    }

    let mut env = [0u16; M];
    for u in toposorted_wire_codes {
        if let Some(instr) = instructions_by_output_wire_code.get(&u) {
            env[instr.out.code as usize] = instr.op.value(&env);
        }
    }

    env[Wire::from_id("a").code as usize]
}

fn main() {
    let instructions: Vec<Instr> = io::stdin()
        .lock()
        .lines()
        .map(|line| Instr::parse(&line.unwrap()))
        .collect();

    let result1 = compute(&instructions, None);
    println!("{}", result1);
    println!("{}", compute(&instructions, Some(result1)));
}
