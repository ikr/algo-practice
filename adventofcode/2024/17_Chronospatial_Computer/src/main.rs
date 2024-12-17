use std::io::{self, BufRead};

fn parse_register_value(s: &str) -> u64 {
    let parts = s.split(": ").collect::<Vec<_>>();
    parts[1].parse().unwrap()
}

fn parse_program(s: &str) -> Vec<u8> {
    let parts = s.split(": ").collect::<Vec<_>>();
    parts[1].split(",").map(|t| t.parse().unwrap()).collect()
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().to_string())
        .collect();

    let registers: [u64; 3] = lines[0..3]
        .iter()
        .map(|line| parse_register_value(line))
        .collect::<Vec<_>>()
        .try_into()
        .unwrap();

    let program = parse_program(&lines[4]);

    eprintln!("registers: {:?} program: {:?}", registers, program);
}
