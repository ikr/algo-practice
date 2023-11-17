use std::io::{self, BufRead};

fn main() {
    let mut result = 0;

    for line in io::stdin().lock().lines() {
        let x: i32 = line.unwrap().trim().parse().unwrap();
        result += x;
    }

    println!("{}", result);
}
