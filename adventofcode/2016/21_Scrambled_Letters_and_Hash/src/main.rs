use std::io::{self, BufRead};

fn extract_pair(prefix: &str, infix: &str, src: &str) -> [String; 2] {
    src.strip_prefix(prefix)
        .unwrap()
        .split(infix)
        .map(|s| s.to_owned())
        .collect::<Vec<_>>()
        .try_into()
        .unwrap()
}

#[derive(Debug)]
enum Op {
    SwpPos(usize, usize),
    SwpLtr(u8, u8),
    RotL(usize),
    RotR(usize),
    Rbop(u8),
    Rev(usize, usize),
    Mov(usize, usize),
}

impl Op {
    fn parse(src: &str) -> Op {
        if src.starts_with("swap p") {
            let [x, y] = extract_pair("swap position ", " with position ", src);
            Op::SwpPos(x.parse().unwrap(), y.parse().unwrap())
        } else {
            panic!("Invalid Op source {}", src)
        }
    }
}

fn main() {
    let ops: Vec<Op> = io::stdin()
        .lock()
        .lines()
        .map(|line| Op::parse(&line.unwrap()))
        .collect();
    eprintln!("{:?}", ops);
}
