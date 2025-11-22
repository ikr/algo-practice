use std::io::{BufRead, stdin};

const ROTATIONS: usize = 202520252025;

fn parse_range(s: &str) -> (u32, u32) {
    let parts = s.split('-').collect::<Vec<_>>();
    (parts[0].parse().unwrap(), parts[1].parse().unwrap())
}

fn main() {
    let input_ranges: Vec<(u32, u32)> = stdin()
        .lock()
        .lines()
        .map(|line| parse_range(&line.unwrap()))
        .collect();

    let mut lhs: Vec<u32> = vec![];
    let mut xs: Vec<u32> = vec![1];

    for (k, (a, b)) in input_ranges.into_iter().enumerate() {
        for x in a..=b {
            if k % 2 == 0 {
                xs.push(x);
            } else {
                lhs.push(x);
            }
        }
    }
    lhs.reverse();
    xs.extend(lhs);

    let n = xs.len();
    println!("{}", xs[ROTATIONS % n]);
}
