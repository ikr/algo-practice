use std::{
    io::{self, BufRead},
    u64,
};

use itertools::Itertools;
use rand::{random, seq::SliceRandom, thread_rng};

const POPULATION: usize = 1000;
const EXTERNALS: usize = 100;

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

struct Machine {
    registers: [u64; 3],
    program: Vec<u8>,
    ip: usize,
    output: Vec<u8>,
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
                self.output.push(x as u8);
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

    fn run(&mut self) {
        while !self.is_halted() {
            self.tick();
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

fn produce_output(program: Vec<u8>, bit_triples_reg_a: &[u8]) -> Vec<u8> {
    let mut m = Machine::new([value_from_bit_triples(bit_triples_reg_a), 0, 0], program);
    m.run();
    m.output
}

#[derive(Clone)]
struct Entity {
    input_tris: Vec<u8>,
    output: Vec<u8>,
}

impl Entity {
    fn new(program: Vec<u8>) -> Entity {
        let input_tris: Vec<u8> = (0..16).map(|_| random::<u8>() % 8).collect();
        let output = produce_output(program, &input_tris);
        Entity { input_tris, output }
    }

    fn fitness(&self, target_output: &[u8]) -> (u8, i64) {
        let matches = self
            .output
            .iter()
            .zip(target_output)
            .take_while(|(a, b)| a == b)
            .count() as u8;

        (matches, -(value_from_bit_triples(&self.input_tris) as i64))
    }

    fn interbreed(&self, program: Vec<u8>, other: Entity) -> Entity {
        let n = self.input_tris.len();
        let i = (random::<u8>() % (n as u8)) as usize;
        let mut input_tris = self.input_tris[0..i].to_vec();
        input_tris.extend(&other.input_tris[i..]);
        let output = produce_output(program, &input_tris);
        Entity { input_tris, output }
    }
}

fn evolve(program: &[u8], es: &[Entity]) -> Vec<Entity> {
    let mut p: Vec<Entity> = es
        .iter()
        .combinations(2)
        .map(|ab| {
            let a = ab[0];
            let b = ab[1];
            a.interbreed(program.to_vec(), b.clone())
        })
        .collect();
    p.sort_by_key(|e| e.fitness(program));
    p.reverse();

    let mut result = p[0..POPULATION - EXTERNALS].to_vec();
    for _ in 0..EXTERNALS {
        result.push(Entity::new(program.to_vec()));
    }

    let mut rng = thread_rng();
    result.shuffle(&mut rng);
    result
}

fn first_gen(program: &[u8]) -> Vec<Entity> {
    let mut result = vec![];
    for _ in 0..POPULATION {
        result.push(Entity::new(program.to_vec()))
    }
    result
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().to_string())
        .collect();

    let program = parse_program(&lines[4]);

    let mut es = first_gen(&program);
    let mut result: u64 = u64::MAX;
    for _ in 0..100_000 {
        es = evolve(&program, &es);
        for e in es.iter() {
            if e.fitness(&program).0 == 16 {
                let input = value_from_bit_triples(&e.input_tris);
                if input < result {
                    result = input;
                    eprintln!("\nFound {}", result);
                }
            }
        }
    }
}
