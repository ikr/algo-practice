use std::io::{BufRead, stdin};

fn decode_line_connections(s: String) -> Vec<usize> {
    s.split(", ")
        .last()
        .and_then(|a| a.strip_prefix("connections="))
        .unwrap()
        .split(',')
        .map(|a| a.parse::<usize>().unwrap() - 1)
        .collect()
}

fn vertices_with_potential(g: &[Vec<usize>], e: &[u16]) -> Vec<usize> {
    e.iter()
        .enumerate()
        .filter_map(|(i, x)| (*x > 1 && !g[i].is_empty()).then_some(i))
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

    loop {
        let ps = vertices_with_potential(&g, &e);
        if ps.is_empty() {
            break;
        }

        let mut ee = e.clone();

        for p in ps {
            for &q in &g[p] {
                ee[q] += e[p] - 1;
            }
        }

        e = ee;
    }

    println!("{}", e.into_iter().sum::<u16>())
}
