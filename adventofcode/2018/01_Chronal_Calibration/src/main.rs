use std::io::{self, BufRead};
use std::collections::HashSet;

fn read_input() -> Vec<i32> {
    let mut xs = Vec::new();
    for line in io::stdin().lock().lines() {
        let x: i32 = line.unwrap().trim().parse().unwrap();
        xs.push(x);
    }
    xs
}

fn first_acc_repeated(xs: &Vec<i32>) -> i32 {
    let mut seen = HashSet::new();
    let mut acc = 0;
    loop {
        for x in xs {
            acc += x;
            if seen.contains(&acc) {
                return acc;
            }
            seen.insert(acc);
        }
    }
}

fn main() {
    let xs = read_input();
    println!("{}", first_acc_repeated(&xs));
}
