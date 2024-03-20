fn main() {
    let xs: Vec<char> = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .chars()
        .collect();

    eprintln!("{:?}", xs);
}
