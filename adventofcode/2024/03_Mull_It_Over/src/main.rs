use regex::Regex;
use std::io::{self, Read};

#[derive(Debug)]
enum Op {
    Mul(i32, i32),
    Do,
    Dont,
}

fn parse_token(s: &str) -> Op {
    let parts: Vec<_> = s.strip_suffix(')').unwrap().split('(').collect();

    match parts[0] {
        "mul" => {
            let args: Vec<i32> = parts[1].split(',').map(|x| x.parse().unwrap()).collect();
            Op::Mul(args[0], args[1])
        }
        "do" => Op::Do,
        "don't" => Op::Dont,
        _ => panic!("Invalid opcode {}", parts[0]),
    }
}

fn main() {
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();

    let tokens: Vec<_> = Regex::new(r"mul\(\d+,\d+\)|do\(\)|don't\(\)")
        .unwrap()
        .find_iter(&input)
        .map(|x| parse_token(x.as_str()))
        .collect();

    let mut yes = true;
    let mut result: i32 = 0;

    for op in tokens {
        match op {
            Op::Mul(a, b) => {
                if yes {
                    result += a * b;
                }
            }
            Op::Do => {
                yes = true;
            }
            Op::Dont => {
                yes = false;
            }
        }
    }

    println!("{}", result);
}
