use std::{
    collections::BTreeMap,
    io::{self, BufRead},
};

#[derive(Debug)]
enum OpCode {
    And,
    Or,
    Xor,
}

impl OpCode {
    fn parse(s: &str) -> Self {
        match s {
            "AND" => Self::And,
            "OR" => Self::Or,
            "XOR" => Self::Xor,
            _ => panic!("Invalid opcode `{}`", s),
        }
    }
}

#[derive(Debug)]
struct Gate {
    opcode: OpCode,
    lhs_id: String,
    rhs_id: String,
    out_id: String,
}

impl Gate {
    fn parse_op(s: &str) -> (OpCode, String, String) {
        let parts = s.split_whitespace().collect::<Vec<_>>();
        (
            OpCode::parse(parts[1]),
            parts[0].to_string(),
            parts[2].to_string(),
        )
    }

    fn parse(s: &str) -> Gate {
        let parts = s.split(" -> ").collect::<Vec<_>>();
        let (opcode, lhs_id, rhs_id) = Gate::parse_op(parts[0]);
        let out_id = parts[1].to_string();
        Gate {
            opcode,
            lhs_id,
            rhs_id,
            out_id,
        }
    }
}

fn parse_input(s: &str) -> (String, u8) {
    let parts = s.split(": ").collect::<Vec<_>>();
    (parts[0].to_string(), parts[1].parse().unwrap())
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().to_string())
        .collect();

    let isep = lines.iter().position(|s| s.is_empty()).unwrap();

    let inputs: BTreeMap<String, u8> = lines[0..isep].iter().map(|s| parse_input(&s)).collect();
    eprintln!("{:?}", inputs);
    let gates: Vec<Gate> = lines[isep + 1..].iter().map(|s| Gate::parse(&s)).collect();
    eprintln!("{:?}", gates);
}
