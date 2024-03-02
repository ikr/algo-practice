fn main() {
    let xs: Vec<i32> = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .lines()
        .map(|x| x.parse().unwrap())
        .collect();

    eprintln!("{:?}", xs);
}
