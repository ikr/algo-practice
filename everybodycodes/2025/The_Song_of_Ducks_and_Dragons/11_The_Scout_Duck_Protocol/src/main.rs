use std::io::{BufRead, stdin};

fn rounds_until_even(xs: Vec<u64>) -> u64 {
    assert!(xs.is_sorted());

    let n: u64 = xs.len() as u64;
    let total: u64 = xs.iter().sum();
    assert_eq!(total % n, 0);
    let average = total / n;

    xs.into_iter()
        .filter_map(|x| if x > average { Some(x - average) } else { None })
        .sum()
}

fn main() {
    let xs: Vec<u64> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().parse().unwrap())
        .collect();

    println!("{}", rounds_until_even(xs));
}
