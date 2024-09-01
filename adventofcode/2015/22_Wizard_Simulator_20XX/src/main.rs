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
    armor: i8,
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

    fn consider_recharge(&self) -> Wizard {
        assert!(self.hit_points >= 0);
        if self.recharge_left > 0 {
            let mut result = *self;
            result.mana += 101;
            result.recharge_left -= 1;
            result
        } else {
            *self
        }
    }
}

#[derive(Clone, Copy, Debug)]
struct Boss {
    hit_points: i8,
    damage: i8,
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

    fn consider_poison(&self) -> Boss {
        assert!(self.hit_points >= 0);
        if self.poison_left > 0 {
            let mut result = *self;
            result.hit_points -= 3;
            result.poison_left -= 1;
            result
        } else {
            *self
        }
    }

    fn act(&self, wizard: &Wizard) -> TurnOutome {
        let boss = self.consider_poison();
        if boss.hit_points <= 0 {
            TurnOutome::WizardWins
        } else {
            let mut recharged_wizard = wizard.consider_recharge();
            let dealt_damage = (self.damage - recharged_wizard.armor).max(1);
            recharged_wizard.hit_points -= dealt_damage;

            if recharged_wizard.hit_points <= 0 {
                TurnOutome::BossWins
            } else {
                TurnOutome::FightContinues(recharged_wizard, boss)
            }
        }
    }
}

enum TurnOutome {
    FightContinues(Wizard, Boss),
    WizardWins,
    BossWins,
}

fn main() {}
