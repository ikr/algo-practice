use itertools::Itertools;
use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();

    let csv: Vec<u32> = buf.trim().split(',').map(|s| s.parse().unwrap()).collect();
    let result = csv.into_iter().counts().into_values().max().unwrap();
    println!("{result}");
}
