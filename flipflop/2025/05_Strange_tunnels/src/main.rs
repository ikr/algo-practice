use std::{collections::HashMap, io::Read};

fn tunnel_index(xs: &[char]) -> HashMap<char, Vec<usize>> {
    xs.iter()
        .enumerate()
        .fold(HashMap::new(), |mut acc, (i, &x)| {
            acc.entry(x).and_modify(|ii| ii.push(i)).or_insert(vec![i]);
            acc
        })
}
fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();
    let xs: Vec<_> = buf.trim().chars().collect();
    eprintln!("{:?}", tunnel_index(&xs));
}
