use std::io::Read;

fn main() {
    let mut input = String::new();
    std::io::stdin().read_to_string(&mut input).unwrap();
    input = input.trim().to_string();

    let result: usize = input
        .chars()
        .filter(|c| c.is_alphabetic())
        .map(|c| {
            (if c.is_ascii_lowercase() {
                ((c as u8) - b'a') + 1
            } else {
                assert!(c.is_ascii_uppercase());
                ((c as u8) - b'A') + 27
            }) as usize
        })
        .sum();
    println!("{}", result);
}
