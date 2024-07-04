use std::io::{self, BufRead};

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
    Cpy(Rval, Rval),
    Inc(Reg),
    Dec(Reg),
    Jnz(Rval, Rval),
    Tgl(Reg),
}

impl Instr {
    fn decode(line: &str) -> Instr {
        let tokens: Vec<String> = line.split(' ').map(|x| x.to_string()).collect();
        let a = || Reg::decode(&tokens[1]);
        let aa = || Rval::decode(&tokens[1]);
        let bb = || Rval::decode(&tokens[2]);

        match tokens[0].as_str() {
            "cpy" => Instr::Cpy(aa(), bb()),
            "inc" => Instr::Inc(a()),
            "dec" => Instr::Dec(a()),
            "jnz" => Instr::Jnz(aa(), bb()),
            "tgl" => Instr::Tgl(a()),
            _ => panic!("Unknown opcode “{}”", tokens[0]),
        }
    }

    fn toggled(&self) -> Instr {
        match self {
            Instr::Cpy(rv_a, rv_b) => Instr::Jnz(*rv_a, *rv_b),
            Instr::Jnz(rv_a, rv_b) => Instr::Cpy(*rv_a, *rv_b),
            Instr::Inc(r) => Instr::Dec(*r),
            Instr::Dec(r) => Instr::Inc(*r),
            Instr::Tgl(r) => Instr::Inc(*r),
        }
    }
}

struct Machine {
    reg: [i64; 4],
    program: Vec<Instr>,
    ip: i64,
}

impl Machine {
    fn new(program: Vec<Instr>) -> Machine {
        Machine {
            reg: [0; 4],
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

    fn tick(&mut self) {
        match &self.program[self.ip as usize] {
            Instr::Cpy(rv, Rval::Reg(r)) => {
                self.write_reg(*r, self.value_of(*rv));
                self.ip += 1;
            }
            Instr::Cpy(_, Rval::Int(_)) => eprintln!("Skipping impossible cpy"),
            Instr::Inc(Reg(r)) => {
                self.write_reg(*r, self.read_reg(*r) + 1);
                self.ip += 1;
            }
            Instr::Dec(Reg(r)) => {
                self.write_reg(*r, self.read_reg(*r) - 1);
                self.ip += 1;
            }
            Instr::Jnz(rv_a, rv_b) => {
                let offset = if self.value_of(*rv_a) != 0 {
                    self.value_of(*rv_b)
                } else {
                    1
                };
                self.ip += offset;
            }
            Instr::Tgl(Reg(r)) => {
                let offset = self.read_reg(*r);
                let index = self.ip + offset;
                if 0 <= index && index < self.program.len() as i64 {
                    let i = index as usize;
                    self.program[i] = self.program[i].toggled();
                }
                self.ip += 1;
            }
        }
    }

    fn run(&mut self) {
        while !self.is_terminated() {
            self.tick();
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
    m.write_reg('a', 7);
    m.run();
    println!("{}", m.read_reg('a'));
}
