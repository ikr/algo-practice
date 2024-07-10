use regex::{Captures, Regex};
use std::io::{self, BufRead};

fn decode_ascii_hex(src: &str) -> String {
    eprintln!("hex {}", src);
    let a = u8::from_str_radix(src, 16).unwrap();
    let b: u8 = if a > 127 { a - 127 } else { a };
    String::from_utf8(vec![b]).unwrap()
}

fn decode(src: &str) -> String {
    let a: String = src
        .strip_prefix('"')
        .and_then(|x| x.strip_suffix('"'))
        .unwrap()
        .replace("\\\\", "\\")
        .replace("\\\"", "\"")
        .to_owned();

    eprintln!("a: {}", a);

    let re = Regex::new(r"(\\x)([a-z0-9][a-z0-9])").unwrap();
    re.replace_all(&a, |caps: &Captures| decode_ascii_hex(&caps[2]))
        .into_owned()
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap())
        .collect();
    eprintln!("{}", decode(lines.last().unwrap()));

    let result = lines
        .into_iter()
        .fold(0, |acc, s| acc + s.len() - decode(&s).len());
    println!("{}", result);
}
