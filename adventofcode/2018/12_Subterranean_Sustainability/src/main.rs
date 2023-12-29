use std::collections::BTreeSet;
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

fn read_ruleset() -> [bool; 32] {
    let mut result: [bool; 32] = [false; 32];
    for bits in 0..31 {
        result[bits] = (bits & (1 << 2)) != 0;
    }

    for line in io::stdin().lock().lines() {
        let (bits, outcome) = parse_rule(&line.unwrap().trim_end());
        result[bits as usize] = outcome
    }
    result
}

fn state_from_source(s: &str) -> BTreeSet<i32> {
    let mut result: BTreeSet<i32> = BTreeSet::new();
    for (i, c) in s.chars().enumerate() {
        if c == '#' {
            result.insert(i as i32);
        }
    }
    result
}

fn current_bits_at(state: &BTreeSet<i32>, i: i32) -> u8 {
    let mut result: u8 = 0;
    for j in 0..5 {
        if state.contains(&(i + j)) {
            result |= 1 << j;
        }
    }
    result
}

fn evolve(ruleset: &[bool; 32], state: &BTreeSet<i32>) -> BTreeSet<i32> {
    let mut result: BTreeSet<i32> = BTreeSet::new();
    let lo = state.first().unwrap_or(&0) - 5;
    let hi = state.last().unwrap_or(&0).clone();

    for i in lo..=hi {
        let bits = current_bits_at(state, i);
        if ruleset[bits as usize] {
            result.insert(i + 2);
        }
    }
    println!("{:?}", result);
    result
}

fn main() {
    let iss = read_initial_state_source();
    skip_input_line();
    let ruleset = read_ruleset();
    let mut state = state_from_source(&iss);

    for _ in 0..20 {
        state = evolve(&ruleset, &state);
    }

    let result: i32 = state.iter().sum();
    println!("{}", result);
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
