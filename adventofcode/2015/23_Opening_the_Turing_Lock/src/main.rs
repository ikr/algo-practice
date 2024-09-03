use std::io::{self, BufRead};

#[derive(Debug, Clone, Copy)]
enum OpCode {
    Hlf,
    Tpl,
    Inc,
    Jmp,
    Jie,
    Jio,
}

impl OpCode {
    fn parse(src: &str) -> OpCode {
        match src {
            "hlf" => OpCode::Hlf,
            "tpl" => OpCode::Tpl,
            "inc" => OpCode::Inc,
            "jmp" => OpCode::Jmp,
            "jie" => OpCode::Jie,
            "jio" => OpCode::Jio,
            _ => panic!("Invalid opcode {}", src),
        }
    }
}

#[derive(Debug, Clone, Copy)]
enum Reg {
    A,
    B,
}

impl Reg {
    fn parse(src: &str) -> Reg {
        match src {
            "a" => Reg::A,
            "b" => Reg::B,
            _ => panic!("Invalid register {}", src),
        }
    }
}

#[derive(Debug, Clone, Copy)]
enum Instr {
    Hlf(Reg),
    Tpl(Reg),
    Inc(Reg),
    Jmp(i32),
    Jie(Reg, i32),
    Jio(Reg, i32),
}

impl Instr {
    fn parse_two_args(src: &str) -> (Reg, i32) {
        let parts = src.split(", ").collect::<Vec<_>>();
        (Reg::parse(parts[0]), parts[1].parse().unwrap())
    }

    fn parse(src: &str) -> Instr {
        match OpCode::parse(&src[0..3]) {
            OpCode::Hlf => Instr::Hlf(Reg::parse(&src[4..])),
            OpCode::Tpl => Instr::Tpl(Reg::parse(&src[4..])),
            OpCode::Inc => Instr::Inc(Reg::parse(&src[4..])),
            OpCode::Jmp => Instr::Jmp(src[4..].parse().unwrap()),
            OpCode::Jie => {
                let (r, o) = Self::parse_two_args(&src[4..]);
                Instr::Jie(r, o)
            }
            OpCode::Jio => {
                let (r, o) = Self::parse_two_args(&src[4..]);
                Instr::Jio(r, o)
            }
        }
    }
}

fn main() {
    let program: Vec<Instr> = io::stdin()
        .lock()
        .lines()
        .map(|line| Instr::parse(&line.unwrap()))
        .collect();

    eprintln!("{:?}", program);
}
