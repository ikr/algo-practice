use std::io::{self, BufRead};

const INPUT_PREFIX: &str = "initial state: ";

fn read_initial_state_source() -> String {
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

fn parse_neigh_bits(s: &str) -> u8 {
    let mut result: u8 = 0;
    for i in 0..s.len() {
        if s.chars().nth(i).unwrap() == '#' {
            result |= 1 << i;
        }
    }
    result
}

fn parse_rule(s: &str) -> (u8, bool) {
    let tokens: Vec<&str> = s.split(" => ").collect();
    (parse_neigh_bits(tokens[0]), tokens[1] == "#")
}

fn main() {
    println!("{}", read_initial_state_source());
    skip_input_line();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn parse_neigh_bits_on_single_self() {
        let result = parse_neigh_bits("..#..");
        assert_eq!(result, 4);
    }

    #[test]
    fn parse_neigh_bits_on_complete_mask() {
        let result = parse_neigh_bits("#####");
        assert_eq!(result, 31);
    }
}
