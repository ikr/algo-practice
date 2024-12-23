use std::io::{self, BufRead};

use ac_library::Dsu;
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

    let mut dsu = Dsu::new(27 * 27);
    for (a, b) in pairs {
        dsu.merge(encode(&a), encode(&b));
    }

    let g = dsu.groups().into_iter().find(|g| g.len() > 1).unwrap();
    eprintln!("{:?}", g);

    let result = g
        .into_iter()
        .combinations(3)
        .filter(|tri| {
            let s: String = tri.iter().map(|&x| decode(x)).collect();
            s.contains('t')
        })
        .count();

    println!("{}", result);
}
