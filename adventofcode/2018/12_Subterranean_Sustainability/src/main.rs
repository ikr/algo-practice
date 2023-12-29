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
        if ruleset[current_bits_at(state, i) as usize] {
            result.insert(i + 2);
        }
    }
    result
}

fn main() {
    let iss = read_initial_state_source();
    skip_input_line();
    let ruleset = read_ruleset();
    let mut state = state_from_source(&iss);
    println!("{:?}", state);

    let initial_reps = 1000;

    for _ in 1..=initial_reps {
        state = evolve(&ruleset, &state);
        println!("{:?}", state);
    }

    let frame_size: i64 = state.len() as i64;
    let lo0: i64 = state.first().unwrap().clone() as i64;
    let step: i64 = state.iter().nth(1).unwrap().clone() as i64 - lo0;

    let total_reps = 50000000000i64;

    let lo: i64 = lo0 + total_reps - initial_reps;
    let hi: i64 = lo + step * (frame_size - 1);
    let result = frame_size * (lo + hi) / 2i64;
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
