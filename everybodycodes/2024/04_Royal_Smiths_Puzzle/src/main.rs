use std::io::{self, BufRead};

fn main() {
    let xs: Vec<i32> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().parse().unwrap())
        .collect();

    let lo: i32 = *xs.iter().min().unwrap();
    let result: i32 = xs.iter().map(|x| x - lo).sum();
    println!("{}", result);
}
