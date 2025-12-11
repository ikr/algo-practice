use itertools::Itertools;
use std::{
    collections::VecDeque,
    io::{BufRead, stdin},
};

const ZER: u8 = b'`';
const M: usize = (b'z' - ZER + 1) as usize;
const G_SZ: usize = (M - 1) * M * M + (M - 1) * M + M;

fn code_of(s: &str) -> usize {
    s.bytes()
        .map(|b| (b - ZER) as usize)
        .fold(0, |acc, x| acc * M + x)
}

fn decode_input_line(s: &str) -> (usize, Vec<usize>) {
    let (u_src, vs_src) = s.split(": ").collect_tuple().unwrap();
    let u = code_of(u_src);
    let vs = vs_src.split(' ').map(code_of).collect();
    (u, vs)
}

fn toposort(g: &[Vec<usize>]) -> Vec<usize> {
    let n = g.len();
    let mut indeg: Vec<usize> = vec![0; n];

    for vs in g.iter() {
        for &v in vs.iter() {
            indeg[v] += 1;
        }
    }

    let mut q: VecDeque<usize> = indeg
        .iter()
        .enumerate()
        .filter_map(|(u, &x)| if x == 0 { Some(u) } else { None })
        .collect();

    let mut result: Vec<usize> = vec![];
    while let Some(u) = q.pop_front() {
        result.push(u);
        for &v in g[u].iter() {
            indeg[v] -= 1;
            if indeg[v] == 0 {
                q.push_back(v);
            }
        }
    }
    result
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let mut g: Vec<Vec<usize>> = vec![vec![]; G_SZ];

    for line in lines {
        let (u, vs) = decode_input_line(&line);
        for v in vs {
            g[u].push(v);
        }
    }

    let seq = toposort(&g);

    // tab[u][d][f] is the number of paths from "svr" to u which pass through "dac" iﬀ d is 1, and
    // pass through "fft" iﬀ f is 1
    let mut tab: Vec<Vec<Vec<usize>>> = vec![vec![vec![0; 2]; 2]; g.len()];
    tab[code_of("svr")][0][0] = 1;

    for u in seq {
        for &v in &g[u] {
            if v == code_of("dac") {
                tab[v][1][0] += tab[u][0][0];
                tab[v][1][1] += tab[u][0][1];
            } else if v == code_of("fft") {
                tab[v][0][1] += tab[u][0][0];
                tab[v][1][1] += tab[u][1][0];
            } else {
                tab[v][0][0] += tab[u][0][0];
                tab[v][1][0] += tab[u][1][0];
                tab[v][0][1] += tab[u][0][1];
                tab[v][1][1] += tab[u][1][1];
            }
        }
    }

    println!("{}", tab[code_of("out")][1][1]);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_code_of() {
        for (argument, expected_result) in
            [("a", 1), ("abc", 1 * M * M + 2 * M + 3), ("zzz", G_SZ - 1)]
        {
            assert_eq!(code_of(argument), expected_result);
        }
    }
}
