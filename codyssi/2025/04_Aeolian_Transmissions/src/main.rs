use std::io::{self, BufRead};

fn memory_units(c: char) -> usize {
    if c.is_ascii_digit() {
        ((c as u8) - b'0') as usize
    } else {
        ((c as u8) - b'A' + 1) as usize
    }
}

fn total_memory_units(s: &str) -> usize {
    s.chars().map(memory_units).sum()
}

fn compress(s: &str) -> String {
    let cs: Vec<char> = s.chars().collect();

    let rle: Vec<(usize, char)> = cs
        .iter()
        .skip(1)
        .fold(vec![(1usize, cs[0])], |mut acc, &c| {
            let (f, prev_c) = *acc.last().unwrap();
            if prev_c == c {
                acc.pop();
                acc.push((f + 1, c));
            } else {
                acc.push((1, c));
            }
            acc
        });

    rle.into_iter().fold(String::new(), |mut acc, (f, c)| {
        acc += &f.to_string();
        acc.push(c);
        acc
    })
}

fn main() {
    let lines: Vec<String> = io::stdin().lock().lines().map(|s| s.unwrap()).collect();
    let compressed: Vec<String> = lines.into_iter().map(|s| compress(&s)).collect();
    let result: usize = compressed.into_iter().map(|s| total_memory_units(&s)).sum();
    println!("{}", result);
}
