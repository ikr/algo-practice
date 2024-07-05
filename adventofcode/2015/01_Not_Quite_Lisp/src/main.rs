fn main() {
    let xs: Vec<u8> = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .to_owned()
        .into_bytes();

    let result = xs
        .into_iter()
        .fold(0, |acc, x| acc + if x == b'(' { 1 } else { -1 });
    println!("{}", result);
}
