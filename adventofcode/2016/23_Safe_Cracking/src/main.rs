use std::io::{self, BufRead};

#[derive(Debug, Clone, Copy)]
struct Reg(char);

impl Reg {
    fn decode(xs: &str) -> Reg {
        match xs.chars().collect::<Vec<char>>()[..] {
            [x] if x.is_ascii_lowercase() => Reg(x),
            _ => panic!("“{}” is not a Reg literal", xs),
        }
    }
}

#[derive(Debug, Clone, Copy)]
enum Rval {
    Reg(char),
    Int(i64),
}

impl Rval {
    fn decode(xs: &str) -> Rval {
        if let Ok(n) = xs.parse::<i64>() {
            Rval::Int(n)
        } else {
            Rval::Reg(Reg::decode(xs).0)
        }
    }
}

#[derive(Debug, Clone, Copy)]
enum Instr {
    Cpy(Rval, Rval),
    Inc(Reg),
    Dec(Reg),
    Jnz(Rval, Rval),
    Tgl(Reg),
}

impl Instr {
    fn decode(line: &str) -> Instr {
        let tokens: Vec<String> = line.split(' ').map(|x| x.to_string()).collect();
        let a = || Reg::decode(&tokens[1]);
        let aa = || Rval::decode(&tokens[1]);
        let bb = || Rval::decode(&tokens[2]);

        match tokens[0].as_str() {
            "cpy" => Instr::Cpy(aa(), bb()),
            "inc" => Instr::Inc(a()),
            "dec" => Instr::Dec(a()),
            "jnz" => Instr::Jnz(aa(), bb()),
            "tgl" => Instr::Tgl(a()),
            _ => panic!("Unknown opcode “{}”", tokens[0]),
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
