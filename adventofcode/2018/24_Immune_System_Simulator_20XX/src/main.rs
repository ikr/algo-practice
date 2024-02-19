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
}

fn inof(src: &str) -> i32 {
    src.parse().unwrap()
}

#[derive(Debug)]
struct Group {
    units: i32,
    unit_hit_points: i32,
    receptivity: Receptivity,
    unit_damage: i32,
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
            unit_damage: inof(&caps[3]),
            attack_type: AttackType {
                name: caps[4].to_string(),
            },
            initiative: inof(&caps[5]),
        }
    }
}

fn receptivity_source(group_source: &str) -> String {
    if let Some(a) = group_source.find('(') {
        let b = group_source.find(')').unwrap();
        group_source[a + 1..b].to_string()
    } else {
        "".to_string()
    }
}

fn main() {
    eprintln!("{:?}", Receptivity::parse(""));
    eprintln!("{:?}", Receptivity::parse("immune to slashing"));
    eprintln!("{:?}", Receptivity::parse("weak to slashing, cold"));
    eprintln!(
        "{:?}",
        Receptivity::parse("weak to radiation; immune to fire, cold")
    );
    eprintln!(
        "{:?}",
        Receptivity::parse("immune to cold; weak to bludgeoning")
    );

    let whole_input: String = std::io::read_to_string(std::io::stdin()).unwrap();
    let team_sources: Vec<&str> = whole_input.split("\n\n").collect();

    for tsrc in team_sources {
        let lines: Vec<&str> = tsrc.split('\n').filter(|x| !x.is_empty()).collect();
        eprintln!("{}", lines[0]);

        for line in &lines[1..] {
            let g = Group::parse(line);
            eprintln!("{:?}", g);
        }
    }
}
