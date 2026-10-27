use std::io::{Read, stdin};

fn first_exceeding_square(a: u32) -> u32 {
    (1..10_000).map(|x| x * x).find(|&x| x >= a).unwrap()
}

fn main() {
    let mut input = String::new();
    stdin().lock().read_to_string(&mut input).unwrap();

    let xs: Vec<u32> = input
        .trim_end()
        .split(',')
        .map(|s| s.parse().unwrap())
        .collect();

    let result: u32 = xs.into_iter().map(|a| first_exceeding_square(a) - a).sum();
    println!("{result}");
}
