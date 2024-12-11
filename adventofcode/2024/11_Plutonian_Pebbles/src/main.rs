use std::io::{self, BufRead};

fn evolve(x: u64) -> Vec<u64> {
    if x == 0 {
        vec![1]
    } else {
        let ds: Vec<u8> = x.to_string().bytes().collect();
        if ds.len() % 2 == 0 {
            let a: String = String::from_utf8(ds[0..ds.len() / 2].to_vec()).unwrap();
            let b: String = String::from_utf8(ds[ds.len() / 2..].to_vec()).unwrap();
            [a, b].iter().map(|x| x.parse().unwrap()).collect()
        } else {
            vec![x * 2024]
        }
    }
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().to_string())
        .collect();

    let mut xs: Vec<u64> = lines[0]
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    eprintln!("{:?}", xs);

    for _ in 0..25 {
        let new_xs: Vec<u64> = xs.iter().flat_map(|&x| evolve(x)).collect();
        xs = new_xs;
    }

    println!("{}", xs.len());
}
