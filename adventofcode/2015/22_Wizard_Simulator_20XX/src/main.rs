use std::collections::VecDeque;

#[derive(Clone, Copy, Debug)]
enum WhoseTurn {
    Wizard,
    Boss,
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

    fn possible_spells(&self, boss: Boss) -> Vec<Spell> {
        let mut result = vec![Spell::MagicMissile, Spell::Drain];

        for (x, s) in [
            (self.shield_left, Spell::Shield),
            (boss.poison_left, Spell::Poison),
            (self.recharge_left, Spell::Recharge),
        ] {
            if x <= 1 {
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
            let mut recharged_wizard = wizard.consider_recharge().consider_shiled();
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

#[derive(Debug, Clone, Copy, PartialEq)]
enum TurnOutome {
    FightContinues(Wizard, Boss),
    WizardWins,
    BossWins,
}

#[derive(Debug, Clone, Copy)]
struct Vertex {
    whose_turn: WhoseTurn,
    wizard: Wizard,
    boss: Boss,
    mana_spent: u16,
}

fn main() {
    let mut q: VecDeque<Vertex> = VecDeque::new();
    q.push_back(Vertex {
        whose_turn: WhoseTurn::Wizard,
        wizard: Wizard::initial(),
        boss: Boss::initial(),
        mana_spent: 0,
    });

    let mut result = u16::MAX;

    while let Some(u) = q.pop_front() {
        match u.whose_turn {
            WhoseTurn::Wizard => {
                assert!(u.wizard.hit_points > 0);
                for spell in u.wizard.possible_spells(u.boss) {
                    match u.wizard.act(spell, u.boss) {
                        TurnOutome::WizardWins => {
                            if u.mana_spent + spell.cost_mana() < result {
                                result = u.mana_spent + spell.cost_mana();
                                println!("{}", result);
                            }
                        }
                        TurnOutome::BossWins => {
                            panic!("{:?} defeats {:?} on opponent's turn", u.boss, u.wizard);
                        }
                        TurnOutome::FightContinues(wizard, boss) => {
                            q.push_back(Vertex {
                                whose_turn: WhoseTurn::Boss,
                                wizard,
                                boss,
                                mana_spent: u.mana_spent + spell.cost_mana(),
                            });
                        }
                    }
                }
            }
            WhoseTurn::Boss => {
                assert!(u.boss.hit_points > 0);
                match u.boss.act(u.wizard) {
                    TurnOutome::WizardWins => {
                        if u.mana_spent < result {
                            result = u.mana_spent;
                            println!("{}", result);
                        }
                    }
                    TurnOutome::BossWins => {
                        // eprintln!("{:?} defeats {:?} on their turn", u.boss, u.wizard);
                    }
                    TurnOutome::FightContinues(wizard, boss) => {
                        q.push_back(Vertex {
                            whose_turn: WhoseTurn::Wizard,
                            wizard,
                            boss,
                            mana_spent: u.mana_spent,
                        });
                    }
                }
            }
        }
    }

    println!("{}", result);
}
