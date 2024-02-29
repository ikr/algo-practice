fn containing_diameter(n: u32) -> u32 {
    let sqr = (n as f64).sqrt() as u32;
    let mut result = sqr.saturating_sub(2);
    while result % 2 == 0 || result * result < n {
        result += 1;
    }
    result
}

fn main() {
    let n: u32 = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .parse()
        .unwrap();
    eprintln!("{}", containing_diameter(n));
}
