fn main() {
    let input_line = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .to_string();
    let xs: Vec<i32> = input_line
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    eprintln!("{:?}", xs);
}
