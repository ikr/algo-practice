use std::io::{self, BufRead};

fn parse_line(s: &str) -> Vec<i32> {
    s.split_whitespace().map(|x| x.parse().unwrap()).collect()
}

fn without(xs: &[i32], i: usize) -> Vec<i32> {
    let mut result = xs.to_vec();
    result.remove(i);
    result
}

fn is_safe(xs0: &[i32]) -> bool {
    (0..xs0.len()).any(|i| {
        let xs = without(xs0, i);
        (xs.windows(2).all(|w| w[0] < w[1]) || xs.windows(2).all(|w| w[0] > w[1]))
            && xs.windows(2).all(|w| w[0].abs_diff(w[1]) <= 3)
    })
}

fn main() {
    let lines: Vec<Vec<i32>> = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_line(&line.unwrap()))
        .collect();

    let result = lines.iter().filter(|row| is_safe(row)).count();
    eprintln!("{:?}", result);
}
