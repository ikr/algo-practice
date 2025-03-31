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

    let mut tree = vec![0u32; 2 << 19];
    for (_, id) in artifacts {
        let mut i: usize = 1;
        loop {
            if tree[i] == 0 {
                tree[i] = id;
                break;
            } else if id < tree[i] {
                i *= 2;
            } else {
                i = i * 2 + 1;
            }
        }
    }

    let sums_by_layer: BTreeMap<usize, u32> = tree
        .iter()
        .enumerate()
        .filter(|(_, x)| **x != 0u32)
        .fold(BTreeMap::new(), |mut acc, (i, id)| {
            let level: usize = (64 - i.leading_zeros()) as usize;
            acc.entry(level).and_modify(|s| *s += id).or_insert(*id);
            acc
        });

    let largest: usize = *sums_by_layer.values().max().unwrap() as usize;
    let result = largest * sums_by_layer.len();
    println!("{}", result);
}
