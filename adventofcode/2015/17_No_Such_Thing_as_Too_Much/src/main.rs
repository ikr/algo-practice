use std::io::{self, BufRead};

const A: i32 = 150;

fn subset_value(xs: &[i32], bits: u32) -> i32 {
    (0..xs.len()).fold(0, |acc, i| {
        if (1u32 << i) & bits != 0 {
            acc + xs[i]
        } else {
            acc
        }
    })
}

fn main() {
    let xs: Vec<_> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().parse::<i32>().unwrap())
        .collect();

    let n = xs.len();

    let result1 = (0..(1 << n))
        .filter(|bits| subset_value(&xs, *bits) == A)
        .count();

    println!("{}", result1);

    let min_subset_size = (0..(1u32 << n))
        .filter(|bits| subset_value(&xs, *bits) == A)
        .map(|bits| bits.count_ones())
        .min()
        .unwrap();

    let result1 = (0..(1u32 << n))
        .filter(|bits| bits.count_ones() == min_subset_size && subset_value(&xs, *bits) == A)
        .count();

    println!("{}", result1);
}
