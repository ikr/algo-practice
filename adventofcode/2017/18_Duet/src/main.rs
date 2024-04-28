use std::io::{self, BufRead};

const AZ: usize = 26;

#[derive(Debug, Clone, Copy)]
struct Reg(char);

impl Reg {
    fn decode(xs: &str) -> Reg {
        match xs.chars().collect::<Vec<char>>()[..] {
            [x] if x.is_ascii_lowercase() => Reg(x),
            _ => panic!("“{}” is not a Reg literal", xs),
        }
    }
}

#[derive(Debug, Clone, Copy)]
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

#[derive(Debug, Clone, Copy)]
enum Instr {
    Snd(Reg),
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
            "snd" => Instr::Snd(a()),
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

enum Outcome {
    Continue,
    ReceiveAndContinue(i64),
    Exit,
}

struct Machine {
    reg: [i64; AZ],
    signal: i64,
    program: Vec<Instr>,
    ip: i64,
}

impl Machine {
    fn new(program: Vec<Instr>) -> Machine {
        Machine {
            reg: [0; AZ],
            signal: 0,
            program,
            ip: 0,
        }
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

    fn value_of(&self, rv: Rval) -> i64 {
        match rv {
            Rval::Reg(r) => self.read_reg(r),
            Rval::Int(v) => v,
        }
    }

    fn tick(&mut self) -> Outcome {
        assert!(!self.is_terminated());

        match &self.program[self.ip as usize] {
            Instr::Snd(Reg(r)) => {
                self.signal = self.read_reg(*r);
                self.ip += 1;
                assert!(!self.is_terminated());
                Outcome::Continue
            }
            Instr::Set(Reg(r), rv) => {
                self.write_reg(*r, self.value_of(*rv));
                self.ip += 1;
                assert!(!self.is_terminated());
                Outcome::Continue
            }
            Instr::Add(Reg(r), rv) => {
                self.write_reg(*r, self.read_reg(*r) + self.value_of(*rv));
                self.ip += 1;
                assert!(!self.is_terminated());
                Outcome::Continue
            }
            Instr::Mul(Reg(r), rv) => {
                self.write_reg(*r, self.read_reg(*r) * self.value_of(*rv));
                self.ip += 1;
                assert!(!self.is_terminated());
                Outcome::Continue
            }
            Instr::Mod(Reg(r), rv) => {
                self.write_reg(*r, self.read_reg(*r) % self.value_of(*rv));
                self.ip += 1;
                assert!(!self.is_terminated());
                Outcome::Continue
            }
            Instr::Rcv(Reg(r)) => {
                if self.read_reg(*r) != 0 {
                    self.write_reg(*r, self.signal);
                }
                self.ip += 1;
                assert!(!self.is_terminated());
                Outcome::ReceiveAndContinue(self.signal)
            }
            Instr::Jgz(rv_a, rv_b) => {
                let offset = if self.value_of(*rv_a) > 0 {
                    self.value_of(*rv_b)
                } else {
                    1
                };

                self.ip += offset;
                if self.is_terminated() {
                    Outcome::Exit
                } else {
                    Outcome::Continue
                }
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

    eprintln!("{:?}", program);

    let mut m = Machine::new(program);
    loop {
        match m.tick() {
            Outcome::Continue => eprint!("."),
            Outcome::ReceiveAndContinue(s) => {
                println!("{}", s);
                break;
            }
            Outcome::Exit => break,
        }
    }
}
