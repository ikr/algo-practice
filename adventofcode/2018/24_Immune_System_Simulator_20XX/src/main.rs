use std::collections::{HashMap, VecDeque};

use regex::Regex;

#[derive(Debug, Clone)]
struct AttackType {
    name: String,
}

impl AttackType {
    fn parse_csv(src: &str) -> Vec<Self> {
        src.split(", ")
            .map(|token| AttackType {
                name: token.to_string(),
            })
            .collect()
    }
}

#[derive(Debug, Clone)]
struct Receptivity {
    immune_to: Vec<AttackType>,
    weak_to: Vec<AttackType>,
}

const WEAK_TO_PREFIX: &str = "weak to ";
const IMMUNE_TO_PREFIX: &str = "immune to ";

impl Receptivity {
    fn parse(src: &str) -> Self {
        let parts: Vec<&str> = src.split("; ").collect();
        let mut immune_to: Vec<AttackType> = vec![];
        let mut weak_to: Vec<AttackType> = vec![];

        for part in parts {
            if let Some(infix) = part.strip_prefix(IMMUNE_TO_PREFIX) {
                immune_to.append(&mut AttackType::parse_csv(infix));
            } else if let Some(infix) = part.strip_prefix(WEAK_TO_PREFIX) {
                weak_to.append(&mut AttackType::parse_csv(infix))
            }
        }

        Self { immune_to, weak_to }
    }

    fn damage_multiplier(&self, attack_type: &AttackType) -> i32 {
        if self.immune_to.iter().any(|a| a.name == attack_type.name) {
            0
        } else if self.weak_to.iter().any(|a| a.name == attack_type.name) {
            2
        } else {
            1
        }
    }
}

fn inof(src: &str) -> i32 {
    src.parse().unwrap()
}

#[derive(Debug, Clone)]
struct Group {
    units: i32,
    unit_hit_points: i32,
    receptivity: Receptivity,
    unit_attack_damage: i32,
    attack_type: AttackType,
    initiative: i32,
}

impl Group {
    fn parse(src: &str) -> Self {
        let r_src = receptivity_source(src);

        let re = Regex::new(
            r"^(\d+) units each with (\d+) hit points.* with an attack that does (\d+) ([a-z]+) damage at initiative (\d+)$",
        ).unwrap();
        let caps = re.captures(src).unwrap();

        Self {
            units: inof(&caps[1]),
            unit_hit_points: inof(&caps[2]),
            receptivity: Receptivity::parse(&r_src),
            unit_attack_damage: inof(&caps[3]),
            attack_type: AttackType {
                name: caps[4].to_string(),
            },
            initiative: inof(&caps[5]),
        }
    }

    fn effective_power(&self) -> i32 {
        self.units * self.unit_attack_damage
    }

    fn is_alive(&self) -> bool {
        self.units > 0
    }

    fn prospective_attack_damage(&self, defender_receptivity: &Receptivity) -> i32 {
        self.effective_power() * defender_receptivity.damage_multiplier(&self.attack_type)
    }

    fn take_damage(&mut self, damage: i32) {
        let units_lost: i32 = damage / self.unit_hit_points;
        self.units -= units_lost;
    }
}

#[derive(Debug, Clone, Copy, Eq, Hash, PartialEq)]
struct GroupHandle {
    army_index: usize,
    group_index: usize,
}

fn receptivity_source(group_source: &str) -> String {
    if let Some(a) = group_source.find('(') {
        let b = group_source.find(')').unwrap();
        group_source[a + 1..b].to_string()
    } else {
        "".to_string()
    }
}

fn all_handles(armies: &[Vec<Group>]) -> VecDeque<GroupHandle> {
    let mut result: VecDeque<GroupHandle> = VecDeque::new();
    for (army_index, army) in armies.iter().enumerate() {
        for (group_index, group) in army.iter().enumerate() {
            assert!(group.is_alive());

            result.push_back(GroupHandle {
                army_index,
                group_index,
            });
        }
    }
    result
}

fn target_selection_queue(armies: &[Vec<Group>]) -> VecDeque<GroupHandle> {
    let mut result = all_handles(armies);
    result.make_contiguous().sort_by_key(|handle| {
        (
            -armies[handle.army_index][handle.group_index].effective_power(),
            -armies[handle.army_index][handle.group_index].initiative,
        )
    });
    result
}

fn attack_queue(armies: &[Vec<Group>]) -> VecDeque<GroupHandle> {
    let mut result = all_handles(armies);
    result
        .make_contiguous()
        .sort_by_key(|handle| -armies[handle.army_index][handle.group_index].initiative);
    result
}

fn enemy_index(own_index: usize) -> usize {
    (own_index + 1) % 2
}

fn select_target(
    taken: &[usize],
    attacking_group: &Group,
    enemy_groups: &[Group],
) -> Option<usize> {
    let available: Vec<usize> = (0..enemy_groups.len())
        .filter(|i| {
            !taken.contains(i)
                && attacking_group.prospective_attack_damage(&enemy_groups[*i].receptivity) > 0
        })
        .collect();

    available
        .iter()
        .max_by_key(|&i| {
            let g: &Group = &enemy_groups[*i];
            let damage: i32 = attacking_group.prospective_attack_damage(&g.receptivity);
            (damage, g.effective_power(), g.initiative)
        })
        .copied()
}

struct Outcome {
    winning_army: usize,
    remaining_units: i32,
    army_names: [String; 2],
}

impl Outcome {
    fn summary(&self) -> String {
        format!(
            "{} wins with {} units remaining",
            self.army_names[self.winning_army], self.remaining_units
        )
    }
}

fn simulate(army_names: &[String], mut armies: [Vec<Group>; 2]) -> Outcome {
    while armies.iter().all(|army| !army.is_empty()) {
        let mut targets: HashMap<GroupHandle, usize> = HashMap::new();
        let mut q0 = target_selection_queue(&armies);
        let mut taken: [Vec<usize>; 2] = [vec![], vec![]];
        while let Some(handle) = q0.pop_front() {
            if let Some(gi) = select_target(
                &taken[enemy_index(handle.army_index)],
                &armies[handle.army_index][handle.group_index],
                &armies[enemy_index(handle.army_index)],
            ) {
                targets.insert(handle, gi);
                taken[enemy_index(handle.army_index)].push(gi);
            }
        }

        let mut q1 = attack_queue(&armies);
        while let Some(handle) = q1.pop_front() {
            if let Some(ig) = targets.get(&handle) {
                if armies[handle.army_index][handle.group_index].is_alive() {
                    let receptivity = &armies[enemy_index(handle.army_index)][*ig].receptivity;
                    let damage = armies[handle.army_index][handle.group_index]
                        .prospective_attack_damage(receptivity);
                    armies[enemy_index(handle.army_index)][*ig].take_damage(damage);
                }
            }
        }

        for army in &mut armies {
            while let Some(i) = army.iter().position(|g| !g.is_alive()) {
                army.remove(i);
            }
        }
    }

    let winning_army = if armies[0].is_empty() { 1 } else { 0 };

    let mut remaining_units = 0;
    for army in armies {
        for group in army {
            remaining_units += group.units;
        }
    }

    Outcome {
        winning_army,
        remaining_units,
        army_names: [army_names[0].clone(), army_names[1].clone()],
    }
}

fn boosted_group(unit_attack_damage_delta: i32, g: &Group) -> Group {
    let mut result = g.clone();
    result.unit_attack_damage += unit_attack_damage_delta;
    result
}

fn boosted_army(unit_attack_damage_delta: i32, a: &[Group]) -> Vec<Group> {
    a.iter()
        .map(|g| boosted_group(unit_attack_damage_delta, g))
        .collect()
}

fn main() {
    let whole_input: String = std::io::read_to_string(std::io::stdin()).unwrap();
    let team_sources: Vec<&str> = whole_input.split("\n\n").collect();
    let mut army_names: [String; 2] = [String::new(), String::new()];
    let mut armies: [Vec<Group>; 2] = [vec![], vec![]];

    for (i, tsrc) in team_sources.iter().enumerate() {
        let lines: Vec<&str> = tsrc.split('\n').filter(|x| !x.is_empty()).collect();
        army_names[i] = lines[0].strip_suffix(':').unwrap().to_string();

        for line in &lines[1..] {
            armies[i].push(Group::parse(line));
        }
    }

    println!("{}", simulate(&army_names, armies).summary());
}
