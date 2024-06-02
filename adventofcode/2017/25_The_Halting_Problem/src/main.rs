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
    position: i32,
    ones_at: HashSet<i32>,
}

fn main() {}
