use itertools::Itertools;

#[derive(Clone, Copy, Debug)]
struct Fighter {
    hit_points: i32,
    damage: i32,
    armor: i32,
}

impl Fighter {
    fn boss() -> Fighter {
        Fighter {
            hit_points: 100,
            damage: 8,
            armor: 2,
        }
    }

    fn player() -> Fighter {
        Fighter {
            hit_points: 100,
            damage: 0,
            armor: 0,
        }
    }

    fn equip(&self, item: &Item) -> Fighter {
        Fighter {
            hit_points: self.hit_points,
            damage: self.damage + item.damage,
            armor: self.armor + item.armor,
        }
    }

    fn attack_return_new_enemy_state(&self, mut enemy: Fighter) -> Fighter {
        assert!(self.hit_points > 0);
        assert!(enemy.hit_points > 0);
        let dealt_damage = (self.damage - enemy.armor).max(1);
        enemy.hit_points -= dealt_damage;
        enemy
    }

    fn simulate_duel_return_winner_index(mut fs: [Fighter; 2]) -> usize {
        let mut i: usize = 0;
        loop {
            let j = (i + 1) % 2;
            fs[j] = fs[i].attack_return_new_enemy_state(fs[j]);
            if fs[j].hit_points <= 0 {
                break;
            }
            i = j;
        }
        i
    }
}

#[derive(Clone, Debug)]
struct Item {
    name: String,
    cost: i32,
    damage: i32,
    armor: i32,
}

impl Item {
    fn from_row(src: (String, i32, i32, i32)) -> Item {
        let (name, cost, damage, armor) = src;
        Item {
            name,
            cost,
            damage,
            armor,
        }
    }

    fn to_vec(src: &[(&str, i32, i32, i32)]) -> Vec<Item> {
        src.iter()
            .map(|(s, c, d, a)| Item::from_row((s.to_string(), *c, *d, *a)))
            .collect()
    }

    fn weapons() -> Vec<Vec<Item>> {
        let xs = Item::to_vec(&[
            ("Dagger", 8, 4, 0),
            ("Shortsword", 10, 5, 0),
            ("Warhammer", 25, 6, 0),
            ("Longsword", 40, 7, 0),
            ("Greataxe", 74, 8, 0),
        ]);

        xs.into_iter().map(|x| vec![x]).collect()
    }

    fn armor() -> Vec<Vec<Item>> {
        let xs = Item::to_vec(&[
            ("Leather", 13, 0, 1),
            ("Chainmail", 31, 0, 2),
            ("Splintmail", 53, 0, 3),
            ("Bandedmail", 75, 0, 4),
            ("Platemail", 102, 0, 5),
        ]);

        let mut result = vec![vec![]];
        result.extend(xs.iter().map(|x| vec![x.clone()]));
        result
    }

    fn rings() -> Vec<Vec<Item>> {
        let xs = Item::to_vec(&[
            ("Damage +1", 25, 1, 0),
            ("Damage +2", 50, 2, 0),
            ("Damage +3", 100, 3, 0),
            ("Defense +1", 20, 0, 1),
            ("Defense +2", 40, 0, 2),
            ("Defense +3", 80, 0, 3),
        ]);

        let ps: Vec<Vec<Item>> = xs
            .iter()
            .combinations(2)
            .map(|a| a.into_iter().cloned().collect::<Vec<_>>())
            .collect();

        let mut result = vec![vec![]];
        result.extend(xs.iter().map(|x| vec![x.clone()]));
        result.extend(ps);
        result
    }
}

fn main() {
    let mut player = Fighter {
        hit_points: 8,
        damage: 5,
        armor: 5,
    };
    let mut boss = Fighter {
        hit_points: 12,
        damage: 7,
        armor: 2,
    };
    eprintln!(
        "{}",
        Fighter::simulate_duel_return_winner_index([player, boss])
    );

    boss = player.attack_return_new_enemy_state(boss);
    eprintln!("{}", boss.hit_points);
    player = boss.attack_return_new_enemy_state(player);
    eprintln!("{}", player.hit_points);

    boss = player.attack_return_new_enemy_state(boss);
    eprintln!("{}", boss.hit_points);
    player = boss.attack_return_new_enemy_state(player);
    eprintln!("{}", player.hit_points);

    boss = player.attack_return_new_enemy_state(boss);
    eprintln!("{}", boss.hit_points);
    player = boss.attack_return_new_enemy_state(player);
    eprintln!("{}", player.hit_points);

    boss = player.attack_return_new_enemy_state(boss);
    eprintln!("{}", boss.hit_points);

    eprintln!("{:?}\n", Item::weapons());
    eprintln!("{:?}\n", Item::armor());
    eprintln!("{:?}", Item::rings());
}
