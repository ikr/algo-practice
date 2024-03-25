use std::{
    collections::HashMap,
    io::{self, BufRead},
};

fn parse_input_line(src: &str) -> (i32, i32) {
    let parts: Vec<String> = src.split(": ").map(|x| x.to_string()).collect();
    let a = parts[0].parse().unwrap();
    let b = parts[1].parse().unwrap();
    (a, b)
}

fn main() {
    let pairs: Vec<(i32, i32)> = io::stdin()
        .lock()
        .lines()
        .map(|l| l.unwrap())
        .map(|l| parse_input_line(&l))
        .collect();

    let ranges_by_depth: HashMap<i32, i32> =
        pairs.into_iter().fold(HashMap::new(), |mut acc, (a, b)| {
            acc.insert(a, b);
            acc
        });

    let mut result = 0;
    for d in 0..100 {
        if let Some(r) = ranges_by_depth.get(&d) {
            if d % (2 * (r - 1)) == 0 {
                result += d * r;
            }
        }
    }
    println!("{}", result);
}
