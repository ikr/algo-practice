use std::io::{self, BufRead};

const AZ: usize = 26;

#[derive(Debug)]
struct Reg(char);

impl Reg {
    fn decode(xs: &str) -> Reg {
        match xs.chars().collect::<Vec<char>>()[..] {
            [x] if x.is_ascii_lowercase() => Reg(x),
            _ => panic!("“{}” is not a Reg literal", xs),
        }
    }
}

#[derive(Debug)]
enum Rval {
    Reg(char),
    Int(i32),
}

impl Rval {
    fn decode(xs: &str) -> Rval {
        if let Ok(n) = xs.parse::<i32>() {
            Rval::Int(n)
        } else {
            Rval::Reg(Reg::decode(xs).0)
        }
    }
}

#[derive(Debug)]
enum Instr {
    Snd(Reg),
    Set(Reg, Rval),
    Add(Reg, Rval),
    Mul(Reg, Rval),
    Mod(Reg, Rval),
    Rcv(Reg),
    Jgz(Rval, Rval),
}

impl Instr {
    fn decode(line: &str) -> Instr {
        let tokens: Vec<String> = line.split(' ').map(|x| x.to_string()).collect();
        let a = || Reg::decode(&tokens[1]);
        let aa = || Rval::decode(&tokens[1]);
        let b = || Rval::decode(&tokens[2]);

        match tokens[0].as_str() {
            "snd" => Instr::Snd(a()),
            "set" => Instr::Set(a(), b()),
            "add" => Instr::Add(a(), b()),
            "mul" => Instr::Mul(a(), b()),
            "mod" => Instr::Mod(a(), b()),
            "rcv" => Instr::Rcv(a()),
            "jgz" => Instr::Jgz(aa(), b()),
            _ => panic!("Unknown opcode “{}”", tokens[0]),
        }
    }
}

struct Machine {
    reg: [i32; AZ],
    signal: i32,
    program: Vec<Instr>,
    ip: usize,
}

impl Machine {
    fn new(program: Vec<Instr>) -> Machine {
        Machine {
            reg: [0; AZ],
            signal: 0,
            program,
            ip: 0,
        }
    }
}

fn main() {
    let program: Vec<Instr> = io::stdin()
        .lock()
        .lines()
        .map(|x| Instr::decode(&x.unwrap()))
        .collect();

    eprintln!("{:?}", program);
}
