use itertools::Itertools;
use std::{
    collections::{HashSet, VecDeque},
    io::{BufRead, stdin},
};

const HI: u64 = 100; //1_000_000;

fn decode_line(s: String) -> (u64, Vec<usize>) {
    let (_, energy_src, connections_src) = s
        .split(", ")
        .map(|x| x.to_string())
        .collect_tuple()
        .unwrap();

    let e: u64 = energy_src.strip_prefix("energy=").unwrap().parse().unwrap();

    let vs: Vec<usize> = connections_src
        .strip_prefix("connections=")
        .unwrap()
        .split(',')
        .map(|a| a.parse::<usize>().unwrap() - 1)
        .collect();

    (e, vs)
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let decoded_lines: Vec<_> = lines.into_iter().map(decode_line).collect();
    let g: Vec<Vec<usize>> = decoded_lines.iter().map(|(_, vs)| vs.clone()).collect();
    let mut e0: Vec<u64> = decoded_lines.into_iter().map(|(x, _)| x).collect();
    let mut e: Vec<u64> = vec![0; g.len()];

    // let i_source: usize = g
    //     .iter()
    //     .enumerate()
    //     .map(|(i, vs)| (i, vs.len()))
    //     .max_by_key(|(_, m)| *m)
    //     .unwrap()
    //     .0;

    let i_source: usize = 2;

    let mut q: VecDeque<(bool, usize, u64)> = VecDeque::from([(false, i_source, 10)]);
    let mut exploded: HashSet<usize> = HashSet::new();

    while let Some((is_explosion, u, x)) = q.pop_front() {
        assert_ne!(x, 0);

        if exploded.contains(&u) {
            assert_eq!(e0[u], 0);
            assert_eq!(e[u], 0);
            continue;
        }

        e[u] += x;

        if e[u] >= HI {
            e0[u] = 0;
            e[u] = 0;
            exploded.insert(u);

            for &v in &g[u] {
                q.push_front((true, v, 10));
            }
        } else if x > 1 {
            for &v in &g[u] {
                if is_explosion && e[v] + x - 1 >= HI {
                    q.push_front((true, v, x - 1));
                } else {
                    q.push_back((false, v, x - 1));
                }
            }
        }
    }

    for u in exploded {
        assert_eq!(e0[u], 0);
        assert_eq!(e[u], 0);
    }

    println!(
        "{}",
        e0.into_iter().zip(e).map(|(x0, x)| x0 + x).sum::<u64>()
    )
}
