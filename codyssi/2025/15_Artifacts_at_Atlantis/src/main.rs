use std::{
    collections::BTreeMap,
    io::{BufRead, stdin},
};

fn parse_line(s: &str) -> (String, u32) {
    let mut parts = s.split(" | ");
    let code = parts.next().unwrap().to_string();
    let id = parts.next().unwrap().parse().unwrap();
    (code, id)
}

fn main() {
    let lines: Vec<_> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let isep = lines.iter().position(|s| s.is_empty()).unwrap();
    let artifacts: Vec<_> = lines[0..isep].iter().map(|s| parse_line(s)).collect();

    let codes_by_id: BTreeMap<u32, String> = artifacts
        .iter()
        .map(|(code, id)| (*id, code.clone()))
        .collect();

    let mut tree = vec![0u32; 2 << 19];
    for (_, id) in artifacts {
        let mut i: usize = 1;
        loop {
            if tree[i] == 0 {
                tree[i] = id;
                break;
            }

            if id < tree[i] {
                i *= 2;
            } else {
                i = i * 2 + 1;
            }
        }
    }

    let mut result: String = String::new();

    {
        let v: u32 = 500000;
        let mut i: usize = 1;
        loop {
            if tree[i] == 0 {
                break;
            } else {
                if !result.is_empty() {
                    result.push('-');
                }
                result.push_str(&codes_by_id[&tree[i]]);
            }

            if v < tree[i] {
                i *= 2;
            } else {
                i = i * 2 + 1;
            }
        }
    }

    println!("{}", result);
}
