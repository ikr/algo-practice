use ac_library::Dsu;
use std::io::{self, BufRead};

fn parse_input_line(src: &str) -> (u16, Vec<u16>) {
    let parts: Vec<String> = src.split(" <-> ").map(|x| x.to_string()).collect();
    let a = parts[0].parse().unwrap();
    let bs: Vec<u16> = parts[1].split(", ").map(|x| x.parse().unwrap()).collect();
    (a, bs)
}

fn main() {
    let lines: Vec<String> = io::stdin().lock().lines().map(|l| l.unwrap()).collect();
    let mut dsu = Dsu::new(lines.len());
    for (u, vs) in lines.iter().map(|l| parse_input_line(l)) {
        for v in vs {
            dsu.merge(u as usize, v as usize);
        }
    }
    println!("{}", dsu.size(0));
}
