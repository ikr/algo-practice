use itertools::Itertools;

#[derive(Debug)]
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
}

#[derive(Debug)]
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

    fn weapons() -> Vec<Item> {
        Item::to_vec(&[
            ("Dagger", 8, 4, 0),
            ("Shortsword", 10, 5, 0),
            ("Warhammer", 25, 6, 0),
            ("Longsword", 40, 7, 0),
            ("Greataxe", 74, 8, 0),
        ])
    }

    fn armor() -> Vec<Item> {
        Item::to_vec(&[
            ("Leather", 13, 0, 1),
            ("Chainmail", 31, 0, 2),
            ("Splintmail", 53, 0, 3),
            ("Bandedmail", 75, 0, 4),
            ("Platemail", 102, 0, 5),
        ])
    }

    fn rings() -> Vec<Item> {
        Item::to_vec(&[
            ("Damage +1", 25, 1, 0),
            ("Damage +2", 50, 2, 0),
            ("Damage +3", 100, 3, 0),
            ("Defense +1", 20, 0, 1),
            ("Defense +2", 40, 0, 2),
            ("Defense +3", 80, 0, 3),
        ])
    }
}

fn main() {}
