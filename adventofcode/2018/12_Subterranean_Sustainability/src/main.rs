use std::io::{self, BufRead};

const INPUT_PREFIX: &str = "initial state: ";

fn main() {
    let mut line = String::new();
    let stdin = io::stdin();
    stdin
        .lock()
        .read_line(&mut line)
        .expect("1st input line read failed");
    println!("{}", &line[INPUT_PREFIX.len()..].trim_end());
}
