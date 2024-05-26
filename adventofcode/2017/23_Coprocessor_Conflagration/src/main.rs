use std::io::{self, BufRead};

const AH: usize = 8;

#[derive(Clone, Copy, Debug)]
struct Reg(char);

impl Reg {
    fn decode(xs: &str) -> Reg {
        match xs.chars().collect::<Vec<char>>()[..] {
            [x] if x.is_ascii_lowercase() => Reg(x),
            _ => panic!("“{}” is not a Reg literal", xs),
        }
    }
}

#[derive(Clone, Copy, Debug)]
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

#[derive(Clone, Copy, Debug)]
enum Instr {
    Set(Reg, Rval),
    Sub(Reg, Rval),
    Mul(Reg, Rval),
    Jnz(Rval, Rval),
}

impl Instr {
    fn decode(line: &str) -> Instr {
        let tokens: Vec<String> = line.split(' ').map(|x| x.to_string()).collect();
        let a = || Reg::decode(&tokens[1]);
        let aa = || Rval::decode(&tokens[1]);
        let b = || Rval::decode(&tokens[2]);

        match tokens[0].as_str() {
            "set" => Instr::Set(a(), b()),
            "sub" => Instr::Sub(a(), b()),
            "mul" => Instr::Mul(a(), b()),
            "jnz" => Instr::Jnz(aa(), b()),
            _ => panic!("Unknown opcode “{}”", tokens[0]),
        }
    }
}

#[derive(Debug)]
struct Machine {
    reg: [i64; AH],
    program: Vec<Instr>,
    ip: i64,
    muls: u32,
}

impl Machine {
    fn new(program: Vec<Instr>) -> Machine {
        Machine {
            reg: [0; AH],
            program,
            ip: 0,
            muls: 0,
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

    fn tick(&mut self) {
        match &self.program[self.ip as usize] {
            Instr::Set(Reg(r), rv) => {
                self.write_reg(*r, self.value_of(*rv));
                self.ip += 1;
            }
            Instr::Sub(Reg(r), rv) => {
                self.write_reg(*r, self.read_reg(*r) - self.value_of(*rv));
                self.ip += 1;
            }
            Instr::Mul(Reg(r), rv) => {
                self.write_reg(*r, self.read_reg(*r) * self.value_of(*rv));
                self.ip += 1;
                self.muls += 1;
            }
            Instr::Jnz(rv_a, rv_b) => {
                let offset = if self.value_of(*rv_a) != 0 {
                    self.value_of(*rv_b)
                } else {
                    1
                };

                self.ip += offset;
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

    let mut m = Machine::new(program);
    while !m.is_terminated() {
        m.tick();
    }
    println!("{}", m.muls);
}
