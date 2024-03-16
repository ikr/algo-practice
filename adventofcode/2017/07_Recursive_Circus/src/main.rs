use std::collections::HashSet;
use std::io::{self, BufRead};

fn parse_vertices_csv(src: &str) -> HashSet<String> {
    if src.is_empty() {
        HashSet::new()
    } else {
        src.split(", ").map(|x| x.to_string()).collect()
    }
}

fn parse_id_and_weight(src: &str) -> (String, i32) {
    let parts: Vec<&str> = src.split(" (").collect();
    let id = parts[0].to_string();
    let weight: i32 = parts[1].strip_suffix(')').unwrap().parse().unwrap();
    (id, weight)
}

#[derive(Debug)]
struct VertexSpec {
    id: String,
    weight: i32,
    adjacent: HashSet<String>,
}

impl VertexSpec {
    fn parse(src: &str) -> VertexSpec {
        let parts: Vec<&str> = src.split(" -> ").collect();
        let (id, weight) = parse_id_and_weight(parts[0]);
        let adjacent = parse_vertices_csv(parts.get(1).unwrap_or(&""));
        VertexSpec {
            id,
            weight,
            adjacent,
        }
    }
}

fn main() {
    let vs: Vec<VertexSpec> = io::stdin()
        .lock()
        .lines()
        .map(|line| VertexSpec::parse(&line.unwrap()))
        .collect();
    eprintln!("{:?}", vs);
}
