use std::io::{self, BufRead};

use itertools::Itertools;

fn parse_register_value(s: &str) -> u64 {
    let parts = s.split(": ").collect::<Vec<_>>();
    parts[1].parse().unwrap()
}

fn parse_program(s: &str) -> Vec<u8> {
    let parts = s.split(": ").collect::<Vec<_>>();
    parts[1].split(",").map(|t| t.parse().unwrap()).collect()
}

enum OpCode {
    Adv,
    Bxl,
    Bst,
    Jnz,
    Bxc,
    Out,
    Bdv,
    Cdv,
}

impl OpCode {
    fn from_u8(value: u8) -> OpCode {
        match value {
            0 => OpCode::Adv,
            1 => OpCode::Bxl,
            2 => OpCode::Bst,
            3 => OpCode::Jnz,
            4 => OpCode::Bxc,
            5 => OpCode::Out,
            6 => OpCode::Bdv,
            7 => OpCode::Cdv,
            _ => panic!("Invalid OpCode value: {}", value),
        }
    }
}

#[derive(Debug)]
struct Machine {
    registers: [u64; 3],
    program: Vec<u8>,
    ip: usize,
    output: Vec<u64>,
}

impl Machine {
    fn new(registers: [u64; 3], program: Vec<u8>) -> Machine {
        Machine {
            registers,
            program,
            ip: 0,
            output: vec![],
        }
    }

    fn eval_combo(&self, x: u8) -> u64 {
        match x {
            0..=3 => x as u64,
            4..=6 => self.registers[(x - 4) as usize],
            _ => panic!("Invalid combo operand {}", x),
        }
    }

    fn is_halted(&self) -> bool {
        self.ip >= self.program.len()
    }

    fn tick(&mut self) {
        assert!(!self.is_halted());
        match OpCode::from_u8(self.program[self.ip]) {
            OpCode::Adv => {
                let p = self.registers[0];
                assert!(self.ip + 1 < self.program.len());
                let q = 2u64.pow(self.eval_combo(self.program[self.ip + 1]) as u32);
                self.registers[0] = p / q;
                self.ip += 2;
            }
            OpCode::Bxl => {
                assert!(self.ip + 1 < self.program.len());
                self.registers[1] ^= self.program[self.ip + 1] as u64;
                self.ip += 2;
            }
            OpCode::Bst => {
                assert!(self.ip + 1 < self.program.len());
                self.registers[1] = self.eval_combo(self.program[self.ip + 1]) % 8;
                self.ip += 2;
            }
            OpCode::Jnz => {
                if self.registers[0] == 0 {
                    self.ip += 2;
                } else {
                    assert!(self.ip + 1 < self.program.len());
                    self.ip = self.program[self.ip + 1] as usize;
                }
            }
            OpCode::Bxc => {
                self.registers[1] ^= self.registers[2];
                assert!(self.ip + 1 < self.program.len());
                self.ip += 2;
            }
            OpCode::Out => {
                assert!(self.ip + 1 < self.program.len());
                let x = self.eval_combo(self.program[self.ip + 1]) % 8;
                self.output.push(x);
                self.ip += 2;
            }
            OpCode::Bdv => {
                let p = self.registers[0];
                assert!(self.ip + 1 < self.program.len());
                let q = 2u64.pow(self.eval_combo(self.program[self.ip + 1]) as u32);
                self.registers[1] = p / q;
                self.ip += 2;
            }
            OpCode::Cdv => {
                let p = self.registers[0];
                assert!(self.ip + 1 < self.program.len());
                let q = 2u64.pow(self.eval_combo(self.program[self.ip + 1]) as u32);
                self.registers[2] = p / q;
                self.ip += 2;
            }
        }
    }
}

fn value_from_bit_triples(xs: &[u8]) -> u64 {
    let mut result: u64 = 0;
    for &x in xs {
        result <<= 3;
        result |= x as u64;
    }
    result
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
    let target: Vec<u64> = program.iter().map(|x| *x as u64).collect();

    let os: Vec<u8> = (0..8).collect();
    let n = target.len();
    for a in (1..n)
        .map(|_| os.clone())
        .multi_cartesian_product()
        .map(|mut xs| {
            xs.push(0);
            value_from_bit_triples(&xs)
        })
    {
        let mut machine = Machine::new(registers, program.clone());
        machine.registers[0] = a;
        while !machine.is_halted() {
            machine.tick();
        }
        if machine.output == target {
            println!("{}", a);
            break;
        } else {
            eprintln!("{} {:?}", machine.output.len(), machine.output);
        }
    }
}
