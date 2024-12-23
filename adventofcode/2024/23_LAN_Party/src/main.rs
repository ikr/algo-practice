use std::io::{self, BufRead};

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

fn contains_t(u: usize) -> bool {
    decode(u).contains('t')
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

    for (u, vs) in g.into_iter().enumerate() {
        if !vs.is_empty() {
            let vss: Vec<String> = vs.iter().map(|v| decode(*v)).collect();
            eprintln!("{} {:?}", decode(u), vss);
        }
    }
}
