use itertools::Itertools;
use std::io::{BufRead, stdin};

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();

    let grid: Vec<Vec<u32>> = lines
        .into_iter()
        .map(|s| s.bytes().map(|x| (x - b'0') as u32).collect())
        .collect();
    eprintln!("{:?}", grid);

    let mut result = 0;
    for row in grid {
        let mut cur = 0;

        for (a, b) in row.into_iter().tuple_combinations() {
            cur = cur.max(a * 10 + b);
        }

        result += cur;
    }
    println!("{result}");
}
