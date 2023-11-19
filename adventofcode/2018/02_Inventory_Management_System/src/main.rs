use std::io::{self, BufRead};

const AZ: usize = (b'z' - b'a' + 1) as usize;

fn read_input() -> Vec<String> {
    let mut xs = Vec::new();
    for line in io::stdin().lock().lines() {
        xs.push(String::from(line.unwrap().trim()));
    }
    xs
}

fn letter_frequences(xs: &str) -> [i32; AZ] {
    let mut freqs = [0; AZ];
    for c in xs.bytes() {
        freqs[usize::from(c - b'a')] += 1;
    }
    freqs
}

fn main() {
    let xs = read_input();
    let fs = xs.iter().map(|x| letter_frequences(x)).collect::<Vec<_>>();
    println!("{:?}", fs);
}
