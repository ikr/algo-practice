use std::{
    collections::HashSet,
    io::{self, BufRead},
};

use itertools::Itertools;

fn parse_line(s: &str) -> (String, String) {
    let parts = s.split("-").collect::<Vec<_>>();
    (parts[0].to_string(), parts[1].to_string())
}

fn encode(s: &str) -> usize {
    let bs = s.as_bytes();
    (bs[0] - b'`') as usize * 27 + (bs[1] - b'`') as usize
}

fn decode(x: usize) -> String {
    String::from_utf8(vec![(x / 27) as u8 + b'`', (x % 27) as u8 + b'`']).unwrap()
}

fn starts_with_t(u: usize) -> bool {
    decode(u).as_bytes()[0] == b't'
}

fn normalize(mut tri: [usize; 3]) -> [usize; 3] {
    tri.sort();
    tri
}

fn main() {
    assert_eq!(decode(encode("fx")), "fx");
    assert_eq!(decode(encode("aa")), "aa");
    assert_eq!(decode(encode("zz")), "zz");
    assert_ne!(decode(encode("zz")), "aa");

    let pairs: Vec<(String, String)> = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_line(&line.unwrap()))
        .collect();

    let mut g: Vec<Vec<usize>> = vec![vec![]; 27 * 27];
    for (u, v) in pairs {
        g[encode(&u)].push(encode(&v));
        g[encode(&v)].push(encode(&u));
    }

    let are_connected = |u: usize, v: usize| g[u].contains(&v);

    let mut tris: HashSet<[usize; 3]> = HashSet::new();

    for (u, vs) in g.iter().enumerate() {
        if vs.len() >= 2 {
            for v1v2 in vs.iter().combinations(2) {
                let v1 = *v1v2[0];
                let v2 = *v1v2[1];
                let tri = normalize([u, v1, v2]);
                if are_connected(v1, v2) && tri.iter().any(|v| starts_with_t(*v)) {
                    tris.insert(tri);
                }
            }
        }
    }

    println!("{}", tris.len());
}
