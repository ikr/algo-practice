use itertools::Itertools;
use std::io::{self, BufRead};

fn read_input() -> Vec<String> {
    let mut xs = Vec::new();
    for line in io::stdin().lock().lines() {
        xs.push(String::from(line.unwrap().trim()));
    }
    xs
}

fn diffs_count(a: &String, b: &String) -> i32 {
    let mut count = 0;
    for (x, y) in a.chars().zip(b.chars()) {
        if x != y {
            count += 1;
        }
    }
    count
}

fn common(a: &String, b: &String) -> String {
    let mut result = String::new();
    for (x, y) in a.chars().zip(b.chars()) {
        if x == y {
            result.push(x);
        }
    }
    result
}

fn main() {
    let xs = read_input();
    for (a, b) in xs.iter().tuple_combinations() {
        if diffs_count(a, b) == 1 {
            println!("{}", common(a, b));
        }
    }
}
