use std::collections::VecDeque;

fn main() {
    let mut istream: VecDeque<i16> = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .split_whitespace()
        .map(|x| x.parse::<i16>().unwrap())
        .collect();

    eprintln!("{:?}", istream)
}
