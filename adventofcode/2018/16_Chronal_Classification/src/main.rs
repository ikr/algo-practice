use std::collections::{HashMap, HashSet};

use strum::IntoEnumIterator;
use strum_macros::EnumIter;

fn read_input_parts() -> (String, String) {
    match std::io::read_to_string(std::io::stdin()) {
        Ok(s) => {
            let parts = s.split("\n\n\n\n").collect::<Vec<&str>>();
            (parts[0].to_string(), parts[1].trim_end().to_string())
        }
        Err(e) => panic!("Error reading from stdin: {}", e),
    }
}

fn split_samples(s: &str) -> Vec<String> {
    s.split("\n\n").map(|s| s.to_string()).collect()
}

type Val = u32;
type Regs = [Val; 4];
type Args = [Val; 3];
type Opcode = u8;
type AbstractInstruction = (Opcode, Args);

#[derive(EnumIter, Eq, Hash, PartialEq, Clone, Debug)]
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

struct Sample {
    before: Regs,
    instruction: AbstractInstruction,
    after: Regs,
}

impl Sample {
    fn parse(s: &str) -> Sample {
        let lines = s.split('\n').collect::<Vec<&str>>();
        let abstract_instruction_quad = parse_quad(" ", lines[1]);
        Sample {
            before: parse_quad(", ", &Sample::infix(lines[0])),
            instruction: (
                abstract_instruction_quad[0] as u8,
                [
                    abstract_instruction_quad[1],
                    abstract_instruction_quad[2],
                    abstract_instruction_quad[3],
                ],
            ),
            after: parse_quad(", ", &Sample::infix(lines[2])),
        }
    }

    fn infix(s: &str) -> String {
        let prefix_length = "Before: [".len();
        s[prefix_length..s.len() - 1].to_string()
    }

    fn possible_ops_count(&self) -> u8 {
        self.possible_ops().len() as u8
    }

    fn possible_ops(&self) -> HashSet<Op> {
        Op::iter().fold(HashSet::new(), |mut acc, op| {
            let mut machine = Machine { regs: self.before };
            machine.apply(&op, &self.instruction.1);
            if machine.regs == self.after {
                acc.insert(op);
            }
            acc
        })
    }
}

fn parse_quad(sep: &str, src: &str) -> [Val; 4] {
    src.split(sep)
        .map(|s| s.parse::<Val>().unwrap())
        .collect::<Vec<Val>>()
        .try_into()
        .unwrap()
}

struct Machine {
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
}

fn solve_part_1(samples: &[Sample]) {
    let result = samples.iter().fold(0, |acc, sample| {
        if sample.possible_ops_count() >= 3 {
            acc + 1
        } else {
            acc
        }
    });

    println!("{}", result);
}

fn parse_program(s: &str) -> Vec<AbstractInstruction> {
    let lines = s.split('\n').collect::<Vec<&str>>();
    lines
        .iter()
        .map(|l| parse_quad(" ", l))
        .map(|q| (q[0] as u8, [q[1], q[2], q[3]]))
        .collect()
}

fn solve_part_2(samples: &[Sample], program: &[AbstractInstruction]) {
    let mut possiblilities: HashMap<u8, HashSet<Op>> = HashMap::new();
    for opcode in 0..16 {
        possiblilities.insert(opcode, Op::iter().collect());
    }

    for sample in samples {
        let cur = possiblilities.get_mut(&sample.instruction.0).unwrap();
        let replacement: HashSet<Op> = cur.intersection(&sample.possible_ops()).cloned().collect();
        *cur = replacement;
    }

    eprintln!("{:?}", possiblilities);
}

fn main() {
    let (samples_source, program_source) = read_input_parts();
    let sample_sources = split_samples(&samples_source);
    let samples: Vec<Sample> = sample_sources.iter().map(|s| Sample::parse(s)).collect();
    solve_part_1(&samples);

    solve_part_2(&samples, &parse_program(&program_source));
}
