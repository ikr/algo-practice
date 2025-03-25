use std::io::{self, BufRead};

fn word_source_to_bytes(s: &str) -> Vec<u8> {
    s.as_bytes()
        .chunks(2)
        .map(|ab| u8::from_str_radix(core::str::from_utf8(ab).unwrap(), 16).unwrap())
        .collect()
}

fn to_u16be(bs: &[u8]) -> Vec<u16> {
    bs.chunks(2)
        .map(|ab| {
            let a = (ab[0] as u16) << 8;
            let b = ab[1] as u16;
            a | b
        })
        .collect()
}

fn to_u16le(bs: &[u8]) -> Vec<u16> {
    bs.chunks(2)
        .map(|ab| {
            let a = ab[0] as u16;
            let b = (ab[1] as u16) << 8;
            a | b
        })
        .collect()
}

fn decode_ascii(bs: &[u8]) -> String {
    let cs: Vec<u8> = bs.iter().map(|&b| if b > 127 { b'?' } else { b }).collect();
    String::from_utf8(cs).unwrap()
}

fn guess_decode(bs: &[u8]) -> String {
    if bs.len() % 2 == 0 {
        if bs[0] == 0 && bs[2] == 0 && bs[4] == 0 {
            String::from_utf16(&to_u16be(bs)).unwrap()
        } else if bs[1] == 0 && bs[3] == 0 && bs[5] == 0 {
            String::from_utf16(&to_u16le(bs)).unwrap()
        } else {
            String::from_utf8(bs.to_vec()).unwrap_or(decode_ascii(bs))
        }
    } else {
        String::from_utf8(bs.to_vec()).unwrap_or(decode_ascii(bs))
    }
}

fn decode(bs: &[u8]) -> String {
    match (bs[0], bs[1], bs[2]) {
        (0xEF, 0xBB, 0xBF) => String::from_utf8(bs[3..].to_vec()).unwrap(),
        (0xFE, 0xFF, _) => String::from_utf16(&to_u16be(&bs[2..])).unwrap(),
        (0xFF, 0xFE, _) => String::from_utf16(&to_u16le(&bs[2..])).unwrap(),
        _ => guess_decode(bs),
    }
}

fn matches(xs: &str, pattern: &str) -> bool {
    xs.chars().count() == pattern.chars().count()
        && xs
            .chars()
            .zip(pattern.chars())
            .all(|(x, y)| y == '.' || x == y)
}

fn matches_any(xs: &str, patterns: &[String]) -> bool {
    patterns.iter().any(|p| matches(xs, p))
}

fn main() {
    let lines: Vec<String> = io::stdin().lock().lines().map(|s| s.unwrap()).collect();
    let isep = lines.iter().position(|s| s.is_empty()).unwrap();

    let word_bytes: Vec<Vec<u8>> = lines[..isep]
        .iter()
        .map(|s| word_source_to_bytes(s))
        .collect();

    let decoded: Vec<(usize, String)> = word_bytes
        .into_iter()
        .enumerate()
        .map(|(i, bs)| (i + 1, decode(&bs)))
        .collect();

    let patterns: Vec<String> = lines[isep + 1..]
        .iter()
        .map(|s| s.trim().to_string())
        .collect();

    let result: usize = decoded
        .into_iter()
        .filter(|(_, s)| matches_any(s, &patterns))
        .map(|(pos, _)| pos)
        .sum();

    println!("{}", result);
}
