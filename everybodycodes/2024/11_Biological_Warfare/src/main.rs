use std::{
    collections::HashSet,
    io::{self, BufRead},
};

fn code_of(xs: &[u8]) -> u16 {
    let n = xs.len();
    (0..n)
        .map(|i| 27u16.pow(i as u32))
        .rev()
        .zip(xs.iter().map(|&x| (x - b'@') as u16))
        .map(|(a, b)| a * b)
        .sum()
}

fn parse_line_rhs(s: &str) -> Vec<u16> {
    s.split(",").map(|s| code_of(s.as_bytes())).collect()
}

fn parse_line(s: &str) -> (u16, Vec<u16>) {
    let parts: Vec<&str> = s.split(":").collect();
    let lhs = code_of(parts[0].as_bytes());
    let rhs = parse_line_rhs(parts[1]);
    (lhs, rhs)
}

fn new_generation(g: &[Vec<u16>], gen: &[usize]) -> Vec<usize> {
    let mut new_gen = vec![0; 27usize.pow(3)];
    for (u, vs) in g.iter().enumerate() {
        for &v in vs {
            new_gen[v as usize] += gen[u];
        }
    }
    new_gen
}

fn main() {
    let g_src: Vec<_> = io::stdin()
        .lock()
        .lines()
        .map(|line| parse_line(&line.unwrap()))
        .collect();

    let vs: HashSet<u16> = g_src.iter().fold(HashSet::new(), |mut acc, (x, ys)| {
        acc.insert(*x);
        for y in ys {
            acc.insert(*y);
        }
        acc
    });

    let g = g_src
        .into_iter()
        .fold(vec![vec![]; 27usize.pow(3)], |mut g, (u, vs)| {
            g[u as usize] = vs;
            g
        });

    let mut lo = usize::MAX;
    let mut hi = 0;

    for x0 in vs {
        let mut gen = vec![0; 27usize.pow(3)];
        gen[x0 as usize] = 1;

        for _ in 0..20 {
            gen = new_generation(&g, &gen);
        }

        let cur = gen.iter().sum::<usize>();
        lo = lo.min(cur);
        hi = hi.max(cur);
    }

    println!("{}", hi - lo);
}
