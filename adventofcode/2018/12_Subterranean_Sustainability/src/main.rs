use std::io::{self, BufRead};

const INPUT_PREFIX: &str = "initial state: ";

fn read_initial_state_source() -> String{
    let mut line = String::new();
    io::stdin()
        .read_line(&mut line)
        .expect("1st input line read failed");

    line[INPUT_PREFIX.len()..].trim_end().to_string()
}

fn skip_input_line() {
    let mut line = String::new();
    io::stdin()
        .read_line(&mut line)
        .expect("Skipping an empty line failed");
}

fn main() {
    println!("{}", read_initial_state_source());
    skip_input_line();
}
