use std::io::Read;

const W: usize = 90;

fn main() {
    let mut buf: String = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();
    let xs: Vec<usize> = buf.trim().split(',').map(|s| s.parse().unwrap()).collect();
    let result: usize = xs.into_iter().map(|x| W / x).sum();
    println!("{result}");
}
