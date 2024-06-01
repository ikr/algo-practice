use std::io::{self, BufRead};

fn decode_pair(src: &str) -> [i32; 2] {
    src.split('/')
        .map(|part| part.parse().unwrap())
        .collect::<Vec<i32>>()
        .try_into()
        .unwrap()
}

fn main() {
    let pairs: Vec<[i32; 2]> = io::stdin()
        .lock()
        .lines()
        .map(|line| decode_pair(&line.unwrap()))
        .collect();
    eprintln!("{:?}", pairs)
}
