fn password_char(salt: &str, x: u32) -> Option<(usize, char)> {
    let input: String = salt.to_owned() + &x.to_string();
    let hash: String = format!("{:?}", md5::compute(input));

    if &hash[0..5] == "00000" {
        let p = hash.chars().nth(5).unwrap();
        if p.is_digit(8) {
            let x = hash.chars().nth(6).unwrap();
            Some((p as usize - b'0' as usize, x))
        } else {
            None
        }
    } else {
        None
    }
}

fn main() {
    let salt: String = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .trim()
        .to_string();

    let mut result = ['.'; 8];
    for i in 0..999_999_999 {
        if i > 0 && i % 1_000_000 == 0 {
            eprintln!("i:{}", i);
        }

        if let Some((p, c)) = password_char(&salt, i) {
            if result[p] == '.' {
                result[p] = c;
            }

            if result.iter().any(|x| *x == '.') {
                eprintln!("{}", result.iter().collect::<String>());
            } else {
                break;
            }
        }
    }
    println!("{}", result.iter().collect::<String>());
}
