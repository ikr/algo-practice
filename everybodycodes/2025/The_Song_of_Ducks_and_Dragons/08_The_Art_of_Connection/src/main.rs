use itertools::Itertools;
use std::io::Read;

const N: usize = 32;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();

    let xs: Vec<usize> = buf
        .trim()
        .split(',')
        .map(|x| x.to_string().parse().unwrap())
        .collect();

    let result = xs
        .into_iter()
        .tuple_windows()
        .filter(|&(x, y)| x.abs_diff(y) == N / 2)
        .count();

    println!("{result}");
}
