use std::{
    collections::VecDeque,
    io::{self, BufRead},
};

const AZ: usize = 26;

#[derive(Clone, Copy)]
struct Reg(char);

impl Reg {
    fn decode(xs: &str) -> Reg {
        match xs.chars().collect::<Vec<char>>()[..] {
            [x] if x.is_ascii_lowercase() => Reg(x),
            _ => panic!("“{}” is not a Reg literal", xs),
        }
    }
}

#[derive(Clone, Copy)]
enum Rval {
    Reg(char),
    Int(i64),
}

impl Rval {
    fn decode(xs: &str) -> Rval {
        if let Ok(n) = xs.parse::<i64>() {
            Rval::Int(n)
        } else {
            Rval::Reg(Reg::decode(xs).0)
        }
    }
}

#[derive(Clone, Copy)]
enum Instr {
    Snd(Rval),
    Set(Reg, Rval),
    Add(Reg, Rval),
    Mul(Reg, Rval),
    Mod(Reg, Rval),
    Rcv(Reg),
    Jgz(Rval, Rval),
}

impl Instr {
    fn decode(line: &str) -> Instr {
        let tokens: Vec<String> = line.split(' ').map(|x| x.to_string()).collect();
        let a = || Reg::decode(&tokens[1]);
        let aa = || Rval::decode(&tokens[1]);
        let b = || Rval::decode(&tokens[2]);

        match tokens[0].as_str() {
            "snd" => Instr::Snd(aa()),
            "set" => Instr::Set(a(), b()),
            "add" => Instr::Add(a(), b()),
            "mul" => Instr::Mul(a(), b()),
            "mod" => Instr::Mod(a(), b()),
            "rcv" => Instr::Rcv(a()),
            "jgz" => Instr::Jgz(aa(), b()),
            _ => panic!("Unknown opcode “{}”", tokens[0]),
        }
    }
}

struct Machine {
    reg: [i64; AZ],
    program: Vec<Instr>,
    ip: i64,
    in_q: VecDeque<i64>,
    out_q: VecDeque<i64>,
    total_sends: u32,
}

#[derive(PartialEq)]
enum TickOutcome {
    Continue,
    Block,
    Terminate,
}

impl Machine {
    fn new(program: Vec<Instr>, id: i64) -> Machine {
        let mut m = Machine {
            reg: [0; AZ],
            program,
            ip: 0,
            in_q: VecDeque::new(),
            out_q: VecDeque::new(),
            total_sends: 0,
        };
        m.reg['p' as usize - 'a' as usize] = id;
        m
    }

    fn read_reg(&self, r: char) -> i64 {
        self.reg[r as usize - 'a' as usize]
    }

    fn write_reg(&mut self, r: char, v: i64) {
        self.reg[r as usize - 'a' as usize] = v;
    }

    fn is_terminated(&self) -> bool {
        self.ip < 0 || self.program.len() as i64 <= self.ip
    }

    fn is_blocked(&self) -> bool {
        self.in_q.is_empty()
    }

    fn value_of(&self, rv: Rval) -> i64 {
        match rv {
            Rval::Reg(r) => self.read_reg(r),
            Rval::Int(v) => v,
        }
    }

    fn tick(&mut self) -> TickOutcome {
        if self.is_terminated() {
            return TickOutcome::Terminate;
        }

        match &self.program[self.ip as usize] {
            Instr::Snd(rv) => {
                self.out_q.push_back(self.value_of(*rv));
                self.total_sends += 1;
                self.ip += 1;
                TickOutcome::Continue
            }
            Instr::Set(Reg(r), rv) => {
                self.write_reg(*r, self.value_of(*rv));
                self.ip += 1;
                TickOutcome::Continue
            }
            Instr::Add(Reg(r), rv) => {
                self.write_reg(*r, self.read_reg(*r) + self.value_of(*rv));
                self.ip += 1;
                TickOutcome::Continue
            }
            Instr::Mul(Reg(r), rv) => {
                self.write_reg(*r, self.read_reg(*r) * self.value_of(*rv));
                self.ip += 1;
                TickOutcome::Continue
            }
            Instr::Mod(Reg(r), rv) => {
                self.write_reg(*r, self.read_reg(*r) % self.value_of(*rv));
                self.ip += 1;
                TickOutcome::Continue
            }
            Instr::Rcv(Reg(r)) => {
                if self.read_reg(*r) != 0 {
                    if let Some(v) = self.in_q.pop_front() {
                        self.write_reg(*r, v);
                        self.ip += 1;
                        TickOutcome::Continue
                    } else {
                        TickOutcome::Block
                    }
                } else {
                    self.ip += 1;
                    TickOutcome::Continue
                }
            }
            Instr::Jgz(rv_a, rv_b) => {
                let offset = if self.value_of(*rv_a) > 0 {
                    self.value_of(*rv_b)
                } else {
                    1
                };

                self.ip += offset;
                TickOutcome::Continue
            }
        }
    }

    fn run(&mut self) {
        loop {
            if self.tick() != TickOutcome::Continue {
                break;
            }
        }
    }
}

fn main() {
    let program: Vec<Instr> = io::stdin()
        .lock()
        .lines()
        .map(|x| Instr::decode(&x.unwrap()))
        .collect();

    let mut m0 = Machine::new(program.clone(), 0);
    let mut m1 = Machine::new(program, 1);

    loop {
        m0.run();
        m1.run();

        while let Some(v) = m0.out_q.pop_front() {
            m1.in_q.push_back(v);
        }

        while let Some(v) = m1.out_q.pop_front() {
            m0.in_q.push_back(v);
        }

        if (m0.is_blocked() || m0.is_terminated()) && (m1.is_blocked() || m1.is_terminated()) {
            break;
        }
    }

    println!("{}", m1.total_sends);
}
