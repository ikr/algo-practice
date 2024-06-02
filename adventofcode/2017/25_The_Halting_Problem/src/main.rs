use std::collections::{HashMap, HashSet};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
enum MoveDir {
    L,
    R,
}

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
enum Val {
    Zero,
    One,
}

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct State(char);

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Outcome(Val, MoveDir, State);

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Cond(State, Val);

fn in_a() -> HashMap<Cond, Outcome> {
    HashMap::from([
        (
            Cond(State('A'), Val::Zero),
            Outcome(Val::One, MoveDir::R, State('B')),
        ),
        (
            Cond(State('A'), Val::One),
            Outcome(Val::Zero, MoveDir::L, State('B')),
        ),
        (
            Cond(State('B'), Val::Zero),
            Outcome(Val::One, MoveDir::L, State('A')),
        ),
        (
            Cond(State('B'), Val::One),
            Outcome(Val::One, MoveDir::R, State('A')),
        ),
    ])
}

struct Machine {
    program: HashMap<Cond, Outcome>,
    num_steps: u32,
    state: State,
    position: i32,
    ones_at: HashSet<i32>,
}

impl Machine {
    fn new(program: HashMap<Cond, Outcome>, num_steps: u32) -> Machine {
        Machine {
            program,
            num_steps,
            state: State('A'),
            position: 0,
            ones_at: HashSet::new(),
        }
    }

    fn current_value(&self) -> Val {
        if self.ones_at.contains(&self.position) {
            Val::One
        } else {
            Val::Zero
        }
    }

    fn tick(&mut self) {
        let k = Cond(self.state, self.current_value());
        if let Some(Outcome(v, d, s)) = self.program.get(&k) {
            self.ones_at.remove(&self.position);
            if *v == Val::One {
                self.ones_at.insert(self.position);
            }

            match d {
                MoveDir::L => self.position -= 1,
                MoveDir::R => self.position += 1,
            }

            self.state = *s;
        } else {
            panic!("No instruction for {:?}", k);
        }
    }

    fn run(&mut self) -> usize {
        for _ in 0..self.num_steps {
            self.tick();
        }
        self.ones_at.len()
    }
}

fn main() {
    for (p, n) in vec![(in_a(), 6)] {
        let mut m = Machine::new(p, n);
        println!("{}", m.run());
    }
}
