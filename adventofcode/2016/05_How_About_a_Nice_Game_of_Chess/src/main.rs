fn password_char(salt: &str, x: u32) -> Option<char> {
    let input: String = salt.to_owned() + &x.to_string();
    let hash: String = format!("{:?}", md5::compute(input));

    if &hash[0..5] == "00000" {
        Some(hash.chars().nth(5).unwrap())
    } else {
        None
    }
}

fn main() {
    let salt: String = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .to_string();

    let mut result: String = String::new();
    for i in 0..999_999_999 {
        if let Some(c) = password_char(&salt, i) {
            result.push(c);
            if result.len() == 8 {
                break;
            }
        }
    }
    println!("{}", result);
}
