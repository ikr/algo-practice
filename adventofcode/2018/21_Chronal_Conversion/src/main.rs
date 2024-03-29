use std::collections::HashSet;
use std::io::{stdin, BufRead};
use std::str::FromStr;
use strum_macros::EnumString;

type Val = u64;
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
        let ra = || self.regs[args[0] as usize];
        let ia = args[0];
        let rb = || self.regs[args[1] as usize];
        let ib = args[1];

        self.regs[args[2] as usize] = match op {
            Op::Addr => ra() + rb(),
            Op::Addi => ra() + ib,
            Op::Mulr => ra() * rb(),
            Op::Muli => ra() * ib,
            Op::Banr => ra() & rb(),
            Op::Bani => ra() & ib,
            Op::Borr => ra() | rb(),
            Op::Bori => ra() | ib,
            Op::Setr => ra(),
            Op::Seti => ia,
            Op::Gtir => {
                if ia > rb() {
                    1
                } else {
                    0
                }
            }
            Op::Gtri => {
                if ra() > ib {
                    1
                } else {
                    0
                }
            }
            Op::Gtrr => {
                if ra() > rb() {
                    1
                } else {
                    0
                }
            }
            Op::Eqir => {
                if ia == rb() {
                    1
                } else {
                    0
                }
            }
            Op::Eqri => {
                if ra() == ib {
                    1
                } else {
                    0
                }
            }
            Op::Eqrr => {
                if ra() == rb() {
                    1
                } else {
                    0
                }
            }
        };
    }

    fn tick_once_return_go_on(&mut self) -> bool {
        assert!(self.regs[self.ip_reg] < self.program.len() as Val);
        // let pre = self.regs.clone();

        let ip = self.regs[self.ip_reg];
        let (op, args) = self.program[ip as usize];
        self.apply(&op, &args);
        self.regs[self.ip_reg] += 1;

        // eprintln!("{}) {:?} {:?}", ip, pre, self.regs);
        self.regs[self.ip_reg] < self.program.len() as Val
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

    let program: Vec<Instr> = stdin()
        .lock()
        .lines()
        .map(|line| parse_instr(&line.unwrap()))
        .collect();

    let mut machine = Machine {
        program,
        ip_reg,
        regs: [0, 0, 0, 0, 0, 0],
    };

    let mut seen: HashSet<Val> = HashSet::new();

    for i in 1..999_999_999_999_999u64 {
        if !machine.tick_once_return_go_on() {
            eprintln!("Done after {} ticks; final state: {:?}", i, machine.regs);
            break;
        }

        match machine.regs[machine.ip_reg] {
            28 => {
                let x = machine.regs[5];
                eprintln!(
                    "i:{} {:?} {}",
                    i,
                    machine.regs,
                    if seen.contains(&x) { "seen" } else { "" }
                );
                if seen.contains(&x) {
                    break;
                }
                seen.insert(x);
            }
            _ => {}
        }
    }
}

// 0 1 2 3 4 5
// A B C D E F

// #ip 4
// 00 F := 123
// 01 F &= 456
// 02 F := F == 72
// 03 E += F
// 04 E := 0

// 05 F := 0
// 06 B := F | 65536
// 07 F := 4591209
// 08 D := B & 255
// 09 F += D
// 10 F &= 16777215
// 11 F *= 65899
// 12 F &= 16777215
// 13 D := B < 256
// 14 E += D
// 15 E += 1
// 16 E := 27
// 17 D := 0

// 18 C := D + 1
// 19 C *= 256
// 20 C := C > B
// 21 E += C
// 22 E += 1
// 23 E := 25
// 24 D += 1
// 25 E := 17

// 26 B := D
// 27 E := 7

// 28 D := A == F
// 29 E += D
// 30 E := 5
