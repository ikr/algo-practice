use std::io::{self, BufRead};

enum OpCode {
    Inc,
    Dec,
}

struct Op {
    reg: String,
    opcode: OpCode,
    arg: i32,
}

enum CmpCode {
    Eq,
    Ge,
    Gt,
    Le,
    Lt,
    Ne,
}

struct Cond {
    reg: String,
    cmpcode: CmpCode,
    arg: i32,
}

fn main() {
    let lines: Vec<String> = io::stdin().lock().lines().map(|x| x.unwrap()).collect();
}
