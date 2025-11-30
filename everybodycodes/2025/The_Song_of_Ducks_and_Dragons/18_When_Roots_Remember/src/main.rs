use regex::Regex;
use std::io::Read;

fn decode_thickness(plant_source: &str) -> u64 {
    eprintln!("{plant_source}\n");
    let re = Regex::new(r"^Plant (\d+) with thickness (\d+):").unwrap();
    let caps = re.captures(plant_source).unwrap();
    caps[2].parse().unwrap()
}

fn main() {
    let mut buf: String = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();
    let plant_sources: Vec<String> = buf
        .trim_end()
        .split("\n\n")
        .map(|s| s.trim_end().to_string())
        .collect();

    let ws: Vec<u64> = plant_sources
        .into_iter()
        .map(|s| decode_thickness(&s))
        .collect();
    eprintln!("{:?} {}", ws, ws.len());
}
