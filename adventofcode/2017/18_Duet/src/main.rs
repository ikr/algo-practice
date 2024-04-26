enum OpCode {
    Snd,
    Set,
    Add,
    Mul,
    Mod,
    Rcv,
    Jgz,
}

enum Rval {
    Reg(char),
    Int(i32),
}

fn main() {
    println!("Hello, world!");
}
