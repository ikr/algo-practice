#[derive(Clone, Copy, Debug)]
enum Turn {
    Wizard,
    Boss,
}

impl Turn {
    fn next(&self) -> Turn {
        match self {
            Turn::Wizard => Turn::Boss,
            Turn::Boss => Turn::Wizard,
        }
    }
}

#[derive(Clone, Copy, Debug)]
enum Spell {
    MagicMissile,
    Drain,
    Shield,
    Poison,
    Recharge,
}

#[derive(Clone, Copy, Debug)]
struct Wizard {
    hit_points: i32,
    armor: i32,
    mana: i32,
}

impl Wizard {
    fn initial() -> Wizard {
        Wizard {
            hit_points: 50,
            armor: 0,
            mana: 500,
        }
    }
}

#[derive(Clone, Copy, Debug)]
struct Boss {
    hit_points: i32,
    damage: i32,
    poison_left: i32,
}

impl Boss {
    fn initial() -> Boss {
        Boss {
            hit_points: 51,
            damage: 9,
            poison_left: 0,
        }
    }
}

fn main() {}
