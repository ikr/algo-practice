use std::{
    collections::VecDeque,
    io::{BufRead, stdin},
};

fn decode_line_connections(s: String) -> Vec<usize> {
    s.split(", ")
        .last()
        .and_then(|a| a.strip_prefix("connections="))
        .unwrap()
        .split(',')
        .map(|a| a.parse::<usize>().unwrap() - 1)
        .collect()
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let g: Vec<Vec<usize>> = lines.into_iter().map(decode_line_connections).collect();
    let mut e: Vec<u16> = vec![0; g.len()];

    let i_source: usize = g
        .iter()
        .enumerate()
        .map(|(i, vs)| (i, vs.len()))
        .max_by_key(|(_, m)| *m)
        .unwrap()
        .0;

    e[i_source] = 5;
    let mut q: VecDeque<(usize, u16)> = VecDeque::from([(i_source, 5)]);

    while let Some((u, x)) = q.pop_front() {
        assert!(x > 1);

        for &v in &g[u] {
            e[v] += x - 1;
            if x - 1 > 1 {
                q.push_back((v, x - 1));
            }
        }
    }

    eprintln!("{e:?}");
    println!("{}", e.into_iter().sum::<u16>())
}
