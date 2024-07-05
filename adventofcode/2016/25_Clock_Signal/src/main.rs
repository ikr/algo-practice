use std::{
    io::{self, BufRead},
    process::exit,
};

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
    Cpy(Rval, Reg),
    Inc(Reg),
    Dec(Reg),
    Jnz(Rval, Rval),
    Out(Reg),
}

impl Instr {
    fn decode(line: &str) -> Instr {
        let tokens: Vec<String> = line.split(' ').map(|x| x.to_string()).collect();
        let a = || Reg::decode(&tokens[1]);
        let aa = || Rval::decode(&tokens[1]);
        let b = || Reg::decode(&tokens[2]);
        let bb = || Rval::decode(&tokens[2]);

        match tokens[0].as_str() {
            "cpy" => Instr::Cpy(aa(), b()),
            "inc" => Instr::Inc(a()),
            "dec" => Instr::Dec(a()),
            "jnz" => Instr::Jnz(aa(), bb()),
            "out" => Instr::Out(a()),
            _ => panic!("Unknown opcode “{}”", tokens[0]),
        }
    }
}

struct Machine {
    reg: [i64; 4],
    program: Vec<Instr>,
    ip: i64,
    output: Vec<i64>,
}

impl Machine {
    fn new(program: Vec<Instr>) -> Machine {
        Machine {
            reg: [0; 4],
            program,
            ip: 0,
            output: vec![],
        }
    }

    fn read_reg(&self, r: char) -> i64 {
        self.reg[r as usize - 'a' as usize]
    }

    fn write_reg(&mut self, r: char, v: i64) {
        self.reg[r as usize - 'a' as usize] = v;
    }

    fn value_of(&self, rv: Rval) -> i64 {
        match rv {
            Rval::Reg(r) => self.read_reg(r),
            Rval::Int(v) => v,
        }
    }

    fn tick(&mut self) {
        match &self.program[self.ip as usize] {
            Instr::Cpy(rv, Reg(r)) => {
                self.write_reg(*r, self.value_of(*rv));
                self.ip += 1;
            }
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
            Instr::Out(Reg(r)) => {
                self.output.push(self.read_reg(*r));
                self.ip += 1;
            }
        }
    }

    fn run(&mut self) {
        for _ in 0..100_000 {
            self.tick();
        }
    }
}

fn is_clock_signal(xs: &[i64]) -> bool {
    xs.len() > 10
        && xs
            .chunks(2)
            .all(|ab| ab.len() == 1 || (ab[0] == 0 && ab[1] == 1))
}

fn main() {
    let program: Vec<Instr> = io::stdin()
        .lock()
        .lines()
        .map(|x| Instr::decode(&x.unwrap()))
        .collect();

    for a in 0..1000 {
        let mut m = Machine::new(program.clone());
        m.write_reg('a', a);
        m.run();

        if is_clock_signal(&m.output) {
            eprintln!("{:?}", m.output);
            println!("{}", a);
            exit(0);
        }
    }
}
