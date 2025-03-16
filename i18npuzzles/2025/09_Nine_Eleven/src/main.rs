use std::io::{self, BufRead};

fn parse_date_source(s: &str) -> [i32; 3] {
    let parts: Vec<i32> = s.split('-').map(|x| x.parse().unwrap()).collect();
    parts.try_into().unwrap()
}

fn parse_names_list(s: &str) -> Vec<String> {
    s.split(", ").map(|x| x.to_string()).collect()
}

fn parse_line(s: &str) -> ([i32; 3], Vec<String>) {
    let parts: Vec<_> = s.split(": ").collect();
    (parse_date_source(parts[0]), parse_names_list(parts[1]))
}

fn main() {
    let lines: Vec<_> = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_line(&line.unwrap()))
        .collect();

    eprintln!("{:?}", lines);
}
