use std::collections::VecDeque;

use regex::Regex;

#[derive(Debug)]
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

#[derive(Debug)]
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

#[derive(Debug)]
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

    fn prospective_attack_damage(&self, defender_receptivity: &Receptivity) -> i32 {
        self.effective_power() * defender_receptivity.damage_multiplier(&self.attack_type)
    }
}

struct GroupId {
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

fn target_selection_queue(armies: &[Vec<Group>]) -> VecDeque<GroupId> {
    todo!()
}

fn main() {
    let whole_input: String = std::io::read_to_string(std::io::stdin()).unwrap();
    let team_sources: Vec<&str> = whole_input.split("\n\n").collect();
    let mut army_names: [String; 2] = [String::new(), String::new()];
    let mut armies: [Vec<Group>; 2] = [vec![], vec![]];

    for (i, tsrc) in team_sources.iter().enumerate() {
        let lines: Vec<&str> = tsrc.split('\n').filter(|x| !x.is_empty()).collect();
        eprintln!("{}", lines[0]);
        army_names[i] = lines[0].strip_suffix(':').unwrap().to_string();

        for line in &lines[1..] {
            armies[i].push(Group::parse(line));
        }
    }

    eprintln!("{:?}", army_names);
    eprintln!("{:?}", armies);
}
