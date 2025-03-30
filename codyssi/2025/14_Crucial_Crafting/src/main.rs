use std::io::{BufRead, stdin};

use regex::Regex;

#[derive(Debug)]
struct Item {
    code: String,
    quality: i32,
    cost: i32,
    unique_materials: i32,
}

impl Item {
    fn parse(s: &str) -> Item {
        let re =
            Regex::new(r"^\d+ (\w+) \| Quality : (\d+), Cost : (\d+), Unique Materials : (\d+)$")
                .unwrap();

        let caps = re.captures(s).unwrap();
        let code: String = caps[1].to_string();
        let quality: i32 = caps[2].parse().unwrap();
        let cost: i32 = caps[3].parse().unwrap();
        let unique_materials: i32 = caps[4].parse().unwrap();

        Item {
            code,
            quality,
            cost,
            unique_materials,
        }
    }
}

fn main() {
    let items: Vec<Item> = stdin()
        .lock()
        .lines()
        .map(|line| Item::parse(&line.unwrap()))
        .collect();
    eprintln!("{:?}", items);
}
