enum OpCode {
    Snd,
    Set,
    Add,
    Mul,
    Mod,
    Rcv,
    Jgz,
}

struct LvalReg(char);

impl LvalReg {
    fn decode(xs: &str) -> LvalReg {
        match xs.chars().collect::<Vec<char>>()[..] {
            [x, ..] if x.is_ascii_lowercase() => LvalReg(x),
            _ => panic!("{} is not a Reg literal", xs),
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
