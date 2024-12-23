use std::io::{self, BufRead};

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

fn represent(vs: &[usize]) -> String {
    let mut ss: Vec<String> = vs.iter().map(|v| decode(*v)).collect();
    ss.sort();
    ss.join(",")
}

fn main() {
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

    let every_pair_is_connected = |vs: &[usize]| {
        vs.iter().combinations(2).all(|v1v2| {
            let v1 = *v1v2[0];
            let v2 = *v1v2[1];
            are_connected(v1, v2)
        })
    };

    let mut hi: Vec<usize> = vec![];
    let mut hi_len: usize = 0;

    for (u, vs) in g.iter().enumerate() {
        if vs.len() >= 2 {
            for vs in vs.iter().cloned().powerset() {
                if every_pair_is_connected(&vs) && vs.len() + 1 > hi_len {
                    hi = vs.clone();
                    hi.push(u);
                    hi_len = vs.len();
                }
            }
        }
    }

    println!("{}", represent(&hi));
}
