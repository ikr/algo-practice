use std::io::{self, BufRead};

fn parse_line_rhs(s: &str) -> Vec<u8> {
    s.split(",").map(|s| s.as_bytes()[0] - b'A').collect()
}

fn parse_line(s: &str) -> (u8, Vec<u8>) {
    let parts: Vec<&str> = s.split(":").collect();
    let lhs = parts[0].as_bytes()[0] - b'A';
    let rhs = parse_line_rhs(parts[1]);
    (lhs, rhs)
}

fn new_generation(g: &[Vec<u8>], gen: &[usize]) -> [usize; 26] {
    let mut new_gen = [0; 26];
    for (u, vs) in g.iter().enumerate() {
        for &v in vs {
            new_gen[v as usize] += gen[u];
        }
    }
    new_gen
}

fn main() {
    let g_src: Vec<(u8, Vec<u8>)> = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_line(&line.unwrap()))
        .collect();

    let g = g_src.into_iter().fold(vec![vec![]; 26], |mut g, (u, vs)| {
        g[u as usize] = vs;
        g
    });

    let mut lo = usize::MAX;
    let mut hi = 0;

    for x0 in 0..3 {
        let mut gen = [0usize; 26];
        gen[x0] = 1;

        for _ in 0..20 {
            gen = new_generation(&g, &gen);
        }

        let cur = gen.iter().sum::<usize>();
        lo = lo.min(cur);
        hi = hi.max(cur);
    }

    println!("{}", hi - lo);
}
