use std::io::{self, BufRead};

fn others(xs: &[i32], i0: usize) -> Vec<i32> {
    xs.iter()
        .enumerate()
        .filter(|(i, _)| *i != i0)
        .map(|ix| *ix.1)
        .collect()
}

fn is_triangle(xs: &[i32]) -> bool {
    !xs.iter()
        .enumerate()
        .any(|(i, x)| *x >= others(&xs, i).into_iter().sum())
}

fn main() {
    let tris: Vec<Vec<i32>> = io::stdin()
        .lock()
        .lines()
        .map(|line| {
            line.unwrap()
                .split_whitespace()
                .map(|src| src.parse().unwrap())
                .collect()
        })
        .collect();

    let result = tris.into_iter().filter(|xs| is_triangle(&xs)).count();
    println!("{}", result);
}
