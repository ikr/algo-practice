use std::io::{self, BufRead};

#[derive(Debug)]
enum OpCode {
    Inc,
    Dec,
}

impl OpCode {
    fn parse(src: &str) -> OpCode {
        match src {
            "inc" => OpCode::Inc,
            "dec" => OpCode::Dec,
            _ => panic!("Invalid OpCode {}", src),
        }
    }

    fn apply(&self, x: i32, arg: i32) -> i32 {
        match self {
            OpCode::Inc => x + arg,
            OpCode::Dec => x - arg,
        }
    }
}

#[derive(Debug)]
struct Op {
    reg: String,
    opcode: OpCode,
    arg: i32,
}

impl Op {
    fn parse(src: &str) -> Op {
        let parts: Vec<&str> = src.split_whitespace().collect();
        let reg = parts[0].to_string();
        let opcode = OpCode::parse(parts[1]);
        let arg: i32 = parts[2].parse().unwrap();
        Op { reg, opcode, arg }
    }
}

#[derive(Debug)]
enum CmpCode {
    Eq,
    Ge,
    Gt,
    Le,
    Lt,
    Ne,
}

impl CmpCode {
    fn parse(src: &str) -> CmpCode {
        match src {
            "==" => CmpCode::Eq,
            ">=" => CmpCode::Ge,
            ">" => CmpCode::Gt,
            "<=" => CmpCode::Le,
            "<" => CmpCode::Lt,
            "!=" => CmpCode::Ne,
            _ => panic!("Invalid CmpCode {}", src),
        }
    }

    fn apply(&self, x: i32, y: i32) -> bool {
        match self {
            CmpCode::Eq => x == y,
            CmpCode::Ge => x >= y,
            CmpCode::Gt => x > y,
            CmpCode::Le => x <= y,
            CmpCode::Lt => x < y,
            CmpCode::Ne => x != y,
        }
    }
}

#[derive(Debug)]
struct Cond {
    reg: String,
    cmpcode: CmpCode,
    arg: i32,
}

impl Cond {
    fn parse(src: &str) -> Cond {
        let parts: Vec<&str> = src.split_whitespace().collect();
        let reg = parts[0].to_string();
        let cmpcode = CmpCode::parse(parts[1]);
        let arg: i32 = parts[2].parse().unwrap();
        Cond { reg, cmpcode, arg }
    }
}

fn main() {
    let lines: Vec<String> = io::stdin().lock().lines().map(|x| x.unwrap()).collect();

    let instructions: Vec<(Op, Cond)> = lines
        .iter()
        .map(|x| {
            let parts: Vec<&str> = x.split(" if ").collect();
            let op = Op::parse(parts[0]);
            let cond = Cond::parse(parts[1]);
            (op, cond)
        })
        .collect();

    eprintln!("{:?}", instructions);
}
