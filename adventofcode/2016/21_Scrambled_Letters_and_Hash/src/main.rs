use std::io::{self, BufRead};

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
            let [x, y] = src
                .strip_prefix("swap position ")
                .unwrap()
                .split(" with position ")
                .map(|s| s.parse::<usize>().unwrap())
                .collect::<Vec<_>>()[..]
            else {
                panic!("SwpPos pair extraction failed for {}", src)
            };
            Op::SwpPos(x, y)
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
