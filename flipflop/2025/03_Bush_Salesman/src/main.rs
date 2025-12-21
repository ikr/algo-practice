use itertools::Itertools;
use std::io::{BufRead, stdin};

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let fqs: Vec<_> = lines.into_iter().counts().into_iter().collect();
    let result = fqs.into_iter().max_by_key(|(_, f)| *f).unwrap().0;
    println!("{result}");
}
