use std::io::{BufRead, stdin};

fn main() {
    let input_seq: Vec<u16> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().parse().unwrap())
        .collect();

    let mut lhs: Vec<u16> = vec![];
    let mut xs: Vec<u16> = vec![1];

    for (k, x) in input_seq.into_iter().enumerate() {
        if k % 2 == 0 {
            xs.push(x);
        } else {
            lhs.push(x);
        }
    }
    lhs.reverse();
    xs.extend(lhs);

    let n = xs.len();
    println!("{}", xs[2025 % n]);
}
