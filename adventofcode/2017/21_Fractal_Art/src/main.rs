use std::io::{self, BufRead};

fn main() {
    let rule_sides: Vec<(String, String)> = io::stdin()
        .lock()
        .lines()
        .map(|line| {
            let parts: Vec<String> = line.unwrap().split(" => ").map(|x| x.to_string()).collect();
            (parts[0].clone(), parts[1].clone())
        })
        .collect();
    eprintln!("{:?}", rule_sides);
}
