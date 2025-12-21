use std::io::{BufRead, stdin};

type Crd = (i32, i32);

fn manhattan_distance(a: Crd, b: Crd) -> i32 {
    todo!()
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    eprintln!("{:?}", lines);
}
