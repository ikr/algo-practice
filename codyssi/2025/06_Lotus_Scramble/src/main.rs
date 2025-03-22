use std::io::Read;

fn main() {
    let mut input = String::new();
    std::io::stdin().read_to_string(&mut input).unwrap();
    input = input.trim().to_string();

    let result = input.chars().filter(|c| c.is_alphabetic()).count();
    println!("{}", result);
}
