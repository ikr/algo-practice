type Val = u32;
type Regs = [Val; 4];
type Args = [Val; 3];

#[derive(Clone, Copy, Debug)]
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

fn main() {
    println!("Hello, world!");
}
