use std::io::{self, BufRead};

fn ops_to_level_at(xs: &[i32], x0: i32) -> i32 {
    xs.iter().map(|x| x.abs_diff(x0) as i32).sum()
}

fn main() {
    let xs: Vec<i32> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().parse().unwrap())
        .collect();

    let mut result = i32::MAX;

    for x0 in xs.iter() {
        let candidate = ops_to_level_at(&xs, *x0);
        if candidate < result {
            result = candidate;
        }
    }

    println!("{}", result);
}
