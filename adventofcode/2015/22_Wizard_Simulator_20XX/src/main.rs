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

#[derive(Clone, Copy, Debug, PartialEq)]
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

#[derive(Clone, Copy, Debug, PartialEq)]
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

    fn possible_spells(&self, boss: Boss) -> Vec<Spell> {
        let mut result = vec![Spell::MagicMissile, Spell::Drain];

        for (x, s) in [
            (self.shield_left, Spell::Shield),
            (boss.poison_left, Spell::Poison),
            (self.recharge_left, Spell::Recharge),
        ] {
            if x == 1 {
                result.push(s);
            }
        }

        let prospective_mana = if self.recharge_left > 0 {
            self.mana + 101
        } else {
            self.mana
        };

        result
            .into_iter()
            .filter(|s| s.cost_mana() <= prospective_mana)
            .collect()
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

    fn consider_shiled(&self) -> Wizard {
        assert!(self.hit_points >= 0);
        if self.shield_left > 0 {
            let mut result = *self;
            result.shield_left -= 1;
            if result.shield_left == 0 {
                result.armor -= 7;
            }
            result
        } else {
            *self
        }
    }

    fn act(&self, casting: Spell, mut boss: Boss) -> TurnOutome {
        boss = boss.consider_poison();
        let mut wizard = self.consider_recharge().consider_shiled();

        assert!(casting.cost_mana() <= wizard.mana);
        wizard.mana -= casting.cost_mana();

        match casting {
            Spell::MagicMissile => {
                boss.hit_points -= 4;
            }
            Spell::Drain => {
                boss.hit_points -= 2;
                wizard.hit_points += 2;
            }
            Spell::Shield => {
                assert_eq!(wizard.shield_left, 0);
                wizard.armor += 7;
                wizard.shield_left = 6;
            }
            Spell::Poison => {
                assert_eq!(boss.poison_left, 0);
                boss.poison_left = 6;
            }
            Spell::Recharge => {
                assert_eq!(wizard.recharge_left, 0);
                wizard.recharge_left = 5;
            }
        }

        if boss.hit_points <= 0 {
            TurnOutome::WizardWins
        } else {
            TurnOutome::FightContinues(wizard, boss)
        }
    }
}

#[derive(Clone, Copy, Debug, PartialEq)]
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

    fn act(&self, wizard: Wizard) -> TurnOutome {
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

#[derive(Debug, PartialEq)]
enum TurnOutome {
    FightContinues(Wizard, Boss),
    WizardWins,
    BossWins,
}

fn main() {
    let mut w = Wizard::example_a();
    let mut b = Boss::example_b();

    {
        assert!(!w.possible_spells(b).is_empty());
        let r = w.act(Spell::Recharge, b);
        match r {
            TurnOutome::FightContinues(ww, bb) => {
                w = ww;
                b = bb;
            }
            _ => panic!("Unexpected outcome {:?}", r),
        }
    }
    assert_eq!(w.hit_points, 10);
    assert_eq!(w.armor, 0);
    assert_eq!(w.mana, 21);
    assert_eq!(b.hit_points, 14);

    {
        assert!(!w.possible_spells(b).is_empty());
        let r = b.act(w);
        match r {
            TurnOutome::FightContinues(ww, bb) => {
                w = ww;
                b = bb;
            }
            _ => panic!("Unexpected outcome {:?}", r),
        }
    }
    assert_eq!(w.hit_points, 2);
    assert_eq!(w.armor, 0);
    assert_eq!(w.mana, 122);
    assert_eq!(b.hit_points, 14);

    {
        assert!(!w.possible_spells(b).is_empty());
        let r = w.act(Spell::Shield, b);
        match r {
            TurnOutome::FightContinues(ww, bb) => {
                w = ww;
                b = bb;
            }
            _ => panic!("Unexpected outcome {:?}", r),
        }
    }
    assert_eq!(w.hit_points, 2);
    assert_eq!(w.armor, 7);
    assert_eq!(w.mana, 110);
    assert_eq!(b.hit_points, 14);
}
