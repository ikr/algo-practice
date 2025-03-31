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
    let artifacts: Vec<_> = lines[..isep].iter().map(|s| parse_line(s)).collect();

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

    let suff: Vec<_> = lines[isep + 1..].iter().map(|s| parse_line(s)).collect();
    assert_eq!(suff.len(), 2);
    let a: u32 = suff[0].1;
    let b: u32 = suff[1].1;

    let mut ia = tree.iter().position(|id| *id == a).unwrap();
    let mut ib = tree.iter().position(|id| *id == b).unwrap();
    while ia != ib {
        if ia < ib {
            ib /= 2;
        } else {
            ia /= 2;
        }
    }

    let result = codes_by_id.get(&tree[ia]).unwrap();
    println!("{}", result);
}
