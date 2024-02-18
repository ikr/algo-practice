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
            if part.starts_with(IMMUNE_TO_PREFIX) {
                immune_to.append(&mut AttackType::parse_csv(&part[IMMUNE_TO_PREFIX.len()..]))
            } else if part.starts_with(WEAK_TO_PREFIX) {
                weak_to.append(&mut AttackType::parse_csv(&part[WEAK_TO_PREFIX.len()..]))
            }
        }

        Self { immune_to, weak_to }
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
    eprintln!("{:?}", team_sources);
}
