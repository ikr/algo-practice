use std::io::{self, BufRead};

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
enum Op {
    Snd(Reg),
    Set(Reg, Rval),
    Add(Reg, Rval),
    Mul(Reg, Rval),
    Mod(Reg, Rval),
    Rcv(Reg),
    Jgz(Rval, Rval),
}

impl Op {
    fn decode(line: &str) -> Op {
        let tokens: Vec<String> = line.split(' ').map(|x| x.to_string()).collect();
        let a = || Reg::decode(&tokens[1]);
        let aa = || Rval::decode(&tokens[1]);
        let b = || Rval::decode(&tokens[2]);

        match tokens[0].as_str() {
            "snd" => Op::Snd(a()),
            "set" => Op::Set(a(), b()),
            "add" => Op::Add(a(), b()),
            "mul" => Op::Mul(a(), b()),
            "mod" => Op::Mod(a(), b()),
            "rcv" => Op::Rcv(a()),
            "jgz" => Op::Jgz(aa(), b()),
            _ => panic!("Unknown opcode “{}”", tokens[0]),
        }
    }
}

fn main() {
    let ops: Vec<Op> = io::stdin()
        .lock()
        .lines()
        .map(|x| Op::decode(&x.unwrap()))
        .collect();

    eprintln!("{:?}", ops);
}
