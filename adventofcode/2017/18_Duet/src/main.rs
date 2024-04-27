use std::io::{self, BufRead};
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

struct Reg(char);

impl Reg {
    fn decode(xs: &str) -> Reg {
        match xs.chars().collect::<Vec<char>>()[..] {
            [x] if x.is_ascii_lowercase() => Reg(x),
            _ => panic!("“{}” is not a Reg literal", xs),
        }
    }
}

enum Rval {
    Reg(char),
    Int(i32),
}

impl Rval {
    fn decode(xs: &str) -> Rval {
        if let Ok(n) = xs.parse::<i32>() {
            Rval::Int(n)
        } else {
            Rval::Reg(Reg::decode(xs).0)
        }
    }
}

fn main() {
    let line_tokens: Vec<Vec<String>> = io::stdin()
        .lock()
        .lines()
        .map(|x| {
            x.unwrap()
                .split(' ')
                .map(|x| x.to_string())
                .collect::<Vec<String>>()
        })
        .collect();

    eprintln!("{:?}", line_tokens);
}
