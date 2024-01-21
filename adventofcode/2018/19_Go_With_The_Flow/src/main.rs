use std::io::{stdin, BufRead};
use std::str::FromStr;
use strum_macros::EnumString;

type Val = u32;
type Regs = [Val; 6];
type Args = [Val; 3];

#[derive(Clone, Copy, Debug, EnumString)]
enum Op {
    Addr,
    Addi,
    Mulr,
    Muli,
    Banr,
    Bani,
    Borr,
    Bori,
    Setr,
    Seti,
    Gtir,
    Gtri,
    Gtrr,
    Eqir,
    Eqri,
    Eqrr,
}

type Instr = (Op, Args);

fn capitalize_first(s: &str) -> String {
    s[..1].to_uppercase() + &s[1..]
}

fn parse_instr(s: &str) -> Instr {
    let parts: Vec<&str> = s.split_whitespace().collect();
    let op: Op = Op::from_str(&capitalize_first(parts[0])).unwrap();
    let args: Args = parts[1..]
        .iter()
        .map(|s| s.parse::<Val>().unwrap())
        .collect::<Vec<Val>>()
        .try_into()
        .unwrap();
    (op, args)
}

struct Machine {
    program: Vec<Instr>,
    ip_reg: usize,
    regs: Regs,
}

impl Machine {
    fn apply(&mut self, op: &Op, args: &Args) {
        let ra = self.regs[args[0] as usize];
        let ia = args[0];
        let rb = self.regs[args[1] as usize];
        let ib = args[1];

        self.regs[args[2] as usize] = match op {
            Op::Addr => ra + rb,
            Op::Addi => ra + ib,
            Op::Mulr => ra * rb,
            Op::Muli => ra * ib,
            Op::Banr => ra & rb,
            Op::Bani => ra & ib,
            Op::Borr => ra | rb,
            Op::Bori => ra | ib,
            Op::Setr => ra,
            Op::Seti => ia,
            Op::Gtir => {
                if ia > rb {
                    1
                } else {
                    0
                }
            }
            Op::Gtri => {
                if ra > ib {
                    1
                } else {
                    0
                }
            }
            Op::Gtrr => {
                if ra > rb {
                    1
                } else {
                    0
                }
            }
            Op::Eqir => {
                if ia == rb {
                    1
                } else {
                    0
                }
            }
            Op::Eqri => {
                if ra == ib {
                    1
                } else {
                    0
                }
            }
            Op::Eqrr => {
                if ra == rb {
                    1
                } else {
                    0
                }
            }
        };
    }

    fn tick_once_return_go_on(&mut self) -> bool {
        assert!(self.regs[self.ip_reg] < self.program.len() as u32);
        let ip = self.regs[self.ip_reg];
        eprintln!("ip: {}, regs: {:?}", ip, self.regs);
        let (op, args) = self.program[ip as usize];
        self.apply(&op, &args);
        self.regs[self.ip_reg] += 1;
        self.regs[self.ip_reg] < self.program.len() as u32
    }
}

fn read_ip() -> usize {
    let mut line = String::new();
    stdin().read_line(&mut line).unwrap();
    let parts: Vec<&str> = line.split_whitespace().collect();
    assert!(parts[0] == "#ip");
    parts[1].parse::<usize>().unwrap()
}

fn main() {
    let ip_reg = read_ip();
    assert!(ip_reg < 6);
    eprintln!("ip: {}", ip_reg);

    let program: Vec<Instr> = stdin()
        .lock()
        .lines()
        .map(|line| parse_instr(&line.unwrap()))
        .collect();

    eprintln!("{:?}", program);

    let mut machine = Machine {
        program,
        ip_reg,
        regs: [0; 6],
    };

    loop {
        if !machine.tick_once_return_go_on() {
            break;
        }
    }
    eprintln!("{:?}", machine.regs);
}
