use std::io::{self, BufRead};

use regex::Regex;

#[derive(Clone, Debug)]
struct Name {
    first: String,
    last: String,
}

impl Name {
    fn english_sort_key(&self) -> (String, String) {
        let ab: Vec<String> = [&self.last, &self.first]
            .into_iter()
            .map(|src| todo!())
            .collect();
        (ab[0], ab[1])
    }
}

fn parse_line(s: &str) -> (Name, u64) {
    let re = Regex::new(r"^(.+), (.+): (\d+)$").unwrap();
    let caps = re.captures(s).unwrap();
    (
        Name {
            first: caps[2].to_string(),
            last: caps[1].to_string(),
        },
        caps[3].parse().unwrap(),
    )
}

fn main() {
    let lines: Vec<_> = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_line(&line.unwrap()))
        .collect();

    eprintln!("{:?}", lines);
}
