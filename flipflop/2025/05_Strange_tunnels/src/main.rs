use std::{collections::HashMap, io::Read, iter::successors};

#[derive(Clone, Copy, Debug, PartialEq)]
enum Phase {
    In,
    Out,
}

fn tunnel_index(xs: Vec<char>) -> HashMap<char, Vec<usize>> {
    xs.iter()
        .enumerate()
        .fold(HashMap::new(), |mut acc, (i, &x)| {
            acc.entry(x).and_modify(|ii| ii.push(i)).or_insert(vec![i]);
            acc
        })
}

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();

    let xs: Vec<_> = buf.trim().chars().collect();
    let n = xs.len();
    let idx = tunnel_index(xs);

    let g: Vec<Vec<usize>> = idx.into_iter().fold(vec![vec![]; n], |mut acc, (_, uv)| {
        let [u, v] = uv.try_into().unwrap();
        acc[u].push(v);
        acc[v].push(u);
        acc
    });

    let trace: Vec<(usize, Phase)> = successors(Some((0, Phase::In)), |&(u, p)| match p {
        Phase::In => Some((g[u][0], Phase::Out)),
        Phase::Out => {
            if u + 1 == n {
                None
            } else {
                Some((u + 1, Phase::In))
            }
        }
    })
    .collect();

    let result: usize = trace
        .chunks(2)
        .map(|ab| {
            let [a, b] = ab.try_into().unwrap();
            a.0.abs_diff(b.0)
        })
        .sum();

    println!("{result}");
}
