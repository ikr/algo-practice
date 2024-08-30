#[derive(Clone, Copy, Debug)]
enum WhoseTurn {
    Wizard,
    Boss,
}

impl WhoseTurn {
    fn next(&self) -> WhoseTurn {
        match self {
            WhoseTurn::Wizard => WhoseTurn::Boss,
            WhoseTurn::Boss => WhoseTurn::Wizard,
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

impl Spell {
    fn cost_mana(&self) -> u16 {
        match self {
            Spell::MagicMissile => 53,
            Spell::Drain => 73,
            Spell::Shield => 113,
            Spell::Poison => 173,
            Spell::Recharge => 229,
        }
    }
}

#[derive(Clone, Copy, Debug)]
struct Wizard {
    hit_points: i8,
    armor: u8,
    mana: u16,
    shield_left: u8,
    recharge_left: u8,
}

impl Wizard {
    fn initial() -> Wizard {
        Wizard {
            hit_points: 50,
            armor: 0,
            mana: 500,
            shield_left: 0,
            recharge_left: 0,
        }
    }

    fn example_a() -> Wizard {
        Wizard {
            hit_points: 10,
            armor: 0,
            mana: 250,
            shield_left: 0,
            recharge_left: 0,
        }
    }
}

#[derive(Clone, Copy, Debug)]
struct Boss {
    hit_points: i8,
    damage: u8,
    poison_left: u8,
}

impl Boss {
    fn initial() -> Boss {
        Boss {
            hit_points: 51,
            damage: 9,
            poison_left: 0,
        }
    }

    fn example_a() -> Boss {
        Boss {
            hit_points: 13,
            damage: 8,
            poison_left: 0,
        }
    }

    fn example_b() -> Boss {
        Boss {
            hit_points: 14,
            damage: 8,
            poison_left: 0,
        }
    }
}

fn main() {}
