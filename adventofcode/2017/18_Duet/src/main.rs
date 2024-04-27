use std::str::FromStr;
use strum_macros::EnumString;

fn uppercase_first(xs: &str) -> String {
    let mut result: Vec<char> = xs.chars().collect();
    result[0] = result[0].to_ascii_uppercase();
    result.into_iter().collect()
}

#[derive(EnumString)]
enum OpCode {
    Snd,
    Set,
    Add,
    Mul,
    Mod,
    Rcv,
    Jgz,
}

impl OpCode {
    fn decode(xs: &str) -> OpCode {
        OpCode::from_str(&uppercase_first(xs)).unwrap()
    }
}

struct LvalReg(char);

impl LvalReg {
    fn decode(xs: &str) -> LvalReg {
        match xs.chars().collect::<Vec<char>>()[..] {
            [x] if x.is_ascii_lowercase() => LvalReg(x),
            _ => panic!("“{}” is not a Reg literal", xs),
        }
    }
}

enum Rval {
    Reg(char),
    Int(i32),
}

struct Op {
    op_code: OpCode,
    lval_reg: LvalReg,
    rval: Rval,
}

fn main() {
    println!("Hello, world!");
}
