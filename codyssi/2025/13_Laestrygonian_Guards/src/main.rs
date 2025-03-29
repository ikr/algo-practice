use std::{
    collections::HashMap,
    io::{BufRead, stdin},
};

fn parse_line(s: &str) -> (String, String, u32) {
    let ab: Vec<_> = s.split(" | ").collect();
    let cd: Vec<_> = ab[0].split(" -> ").collect();
    (cd[0].to_string(), cd[1].to_string(), ab[1].parse().unwrap())
}

fn cycle_length(g: &[Vec<(usize, u32)>], path_so_far: &[usize], length_so_far: u32) -> Option<u32> {
    let u0 = *path_so_far.first().expect("Cycle start must be present");
    let u = *path_so_far.last().unwrap();
    let mut p = path_so_far.to_vec();

    for &(v, w) in g[u].iter() {
        if v == u0 {
            return Some(length_so_far + w);
        }

        if path_so_far.contains(&v) {
            return None;
        }

        p.push(v);
        let sub = cycle_length(g, &p, length_so_far + w);
        if sub.is_some() {
            return sub;
        }
        p.pop();
    }

    None
}

fn main() {
    let lines: Vec<_> = stdin()
        .lock()
        .lines()
        .map(|line| parse_line(&line.unwrap()))
        .collect();

    let idx: HashMap<String, usize> =
        lines
            .iter()
            .flat_map(|(u, v, _)| vec![u, v])
            .fold(HashMap::new(), |mut acc, u| {
                let n = acc.len();
                acc.entry(u.to_string()).or_insert(n);
                acc
            });

    let n = idx.len();
    let g: Vec<Vec<(usize, u32)>> =
        lines
            .into_iter()
            .fold(vec![vec![]; n], |mut acc, (u, v, w)| {
                acc[idx[&u]].push((idx[&v], w));
                acc
            });

    let ls: Vec<_> = (0..n).filter_map(|u| cycle_length(&g, &[u], 0)).collect();
    let result = ls.into_iter().max().unwrap();
    println!("{}", result);
}
