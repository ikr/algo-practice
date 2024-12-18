use std::io::{self, BufRead};

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

struct Backtracking {
    program: Vec<u8>,
    solution_bit_triples: Option<Vec<u8>>,
}

fn tails_equal<T: PartialEq + Copy>(ignore_first_k: usize, xs: &[T], ys: &[T]) -> bool {
    let n = xs.len().saturating_sub(ignore_first_k);
    let tx: Vec<T> = xs.iter().rev().copied().collect();
    let ty: Vec<T> = ys.iter().rev().copied().collect();
    tx[0..n] == ty[0..n.min(ys.len())]
}

impl Backtracking {
    fn new(program: Vec<u8>) -> Self {
        Backtracking {
            program,
            solution_bit_triples: None,
        }
    }

    fn backtrack(&mut self, candidate_bit_triples: Vec<u8>) {
        if self.solution_bit_triples.is_some() || self.reject(&candidate_bit_triples) {
            return;
        }

        if self.accept(&candidate_bit_triples) {
            self.solution_bit_triples = Some(candidate_bit_triples);
            return;
        }

        let mut cur = self.first(candidate_bit_triples);
        while let Some(cur_inner) = cur {
            self.backtrack(cur_inner.clone());
            cur = self.next(cur_inner);
        }
    }

    fn produce_output(&self, bit_triples_reg_a: &[u8]) -> Vec<u8> {
        let mut m = Machine::new(
            [value_from_bit_triples(bit_triples_reg_a), 0, 0],
            self.program.clone(),
        );
        m.run();
        m.output
    }

    fn reject(&self, candidate_bit_triples: &[u8]) -> bool {
        if candidate_bit_triples.is_empty() {
            false
        } else if candidate_bit_triples.len() > self.program.len() + 1 {
            true
        } else {
            let output = self.produce_output(candidate_bit_triples);
            output.len() > self.program.len() || !tails_equal(3, &output, &self.program)
        }
    }

    fn accept(&self, candidate_bit_triples: &[u8]) -> bool {
        let output = self.produce_output(candidate_bit_triples);
        output == self.program
    }

    fn first(&self, mut candidate_bit_triples: Vec<u8>) -> Option<Vec<u8>> {
        candidate_bit_triples.insert(0, 0);
        Some(candidate_bit_triples)
    }

    fn next(&self, mut candidate_bit_triples: Vec<u8>) -> Option<Vec<u8>> {
        assert!(!candidate_bit_triples.is_empty());

        let lim = candidate_bit_triples.len().min(3);

        let rightmost_bumpable_index = candidate_bit_triples[0..lim]
            .iter()
            .enumerate()
            .rev()
            .find(|(_, &x)| x != 7)
            .map(|(i, _)| i);

        if let Some(i) = rightmost_bumpable_index {
            candidate_bit_triples[i] += 1;
            if i < lim - 1 {
                for j in i + 1..lim {
                    candidate_bit_triples[j] = 0;
                }
            }
            Some(candidate_bit_triples)
        } else {
            None
        }
    }

    fn solution_numeric_value(&self) -> Option<u64> {
        self.solution_bit_triples
            .clone()
            .map(|tris| value_from_bit_triples(&tris))
    }
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().to_string())
        .collect();

    let program = parse_program(&lines[4]);
    let mut bt = Backtracking::new(program);
    bt.backtrack(vec![]);
    println!("{:?}", bt.solution_numeric_value());
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn tails_equal_works() {
        for (k, xs, ys, expected) in [
            (0, vec![], vec![], true),
            (0, vec![1], vec![2], false),
            (1, vec![1], vec![2], true),
            (3, vec![7, 7, 7, 4, 3, 0], vec![0, 0, 3, 5, 4, 3, 0], true),
            (3, vec![7, 7, 7, 4, 3, 0], vec![4, 3, 0], true),
            (3, vec![4, 3, 2], vec![0, 0, 3, 5, 7, 7, 7], true),
            (3, vec![4, 3, 2, 0], vec![0, 0, 3, 5], false),
            (2, vec![1, 2, 3], vec![1, 2, 3], true),
            (3, vec![1, 2, 3, 1, 2, 3], vec![1, 2, 3, 1, 2, 3], true),
            (0, vec![1, 2, 3], vec![1, 2, 3], true),
            (0, vec![], vec![1, 2, 3], true),
            (0, vec![1, 2], vec![3], false),
            (1, vec![1, 2], vec![3], false),
            (1, vec![1, 2], vec![2], true),
        ] {
            assert_eq!(tails_equal::<u8>(k, &xs, &ys), expected);
        }
    }

    #[test]
    fn backtracking_next_works() {
        let program: Vec<u8> = vec![0, 3, 5, 4, 3, 0];
        let bt = Backtracking::new(program);

        assert_eq!(bt.next(vec![0]), Some(vec![1]));
        assert_eq!(bt.next(vec![7]), None);
        assert_eq!(bt.next(vec![7, 7]), None);
        assert_eq!(bt.next(vec![3, 7]), Some(vec![4, 0]));
        assert_eq!(bt.next(vec![6, 7, 7]), Some(vec![7, 0, 0]));
        assert_eq!(bt.next(vec![7, 7, 7, 0]), None);
        assert_eq!(bt.next(vec![1, 4, 1, 1]), Some(vec![1, 4, 2, 1]));
    }
}
