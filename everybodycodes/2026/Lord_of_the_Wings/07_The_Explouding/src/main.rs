use itertools::Itertools;
use std::{
    collections::{HashSet, VecDeque},
    io::{BufRead, stdin},
};

const HI: u32 = 100; //1_000_000;

fn decode_line(s: String) -> (u32, Vec<usize>) {
    let (_, energy_src, connections_src) = s
        .split(", ")
        .map(|x| x.to_string())
        .collect_tuple()
        .unwrap();

    let e: u32 = energy_src.strip_prefix("energy=").unwrap().parse().unwrap();

    let vs: Vec<usize> = connections_src
        .strip_prefix("connections=")
        .unwrap()
        .split(',')
        .map(|a| a.parse::<usize>().unwrap() - 1)
        .collect();

    (e, vs)
}

fn simulate_clouds_return_energy(
    g: &[Vec<usize>],
    i_source: usize,
    initial_impulse: u32,
) -> Vec<u32> {
    let mut e: Vec<u32> = vec![0; g.len()];
    let mut q: VecDeque<(usize, u32)> = VecDeque::from([(i_source, initial_impulse)]);

    while let Some((u, x)) = q.pop_front() {
        assert_ne!(x, 0);

        e[u] += x;

        if x > 1 {
            for &v in &g[u] {
                q.push_back((v, x - 1));
            }
        }
    }

    e
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let decoded_lines: Vec<_> = lines.into_iter().map(decode_line).collect();
    let g: Vec<Vec<usize>> = decoded_lines.iter().map(|(_, vs)| vs.clone()).collect();
    let e0: Vec<u32> = decoded_lines.into_iter().map(|(x, _)| x).collect();

    let i_source: usize = g
        .iter()
        .enumerate()
        .map(|(i, vs)| (i, vs.len()))
        .max_by_key(|(_, m)| *m)
        .unwrap()
        .0;

    let e = simulate_clouds_return_energy(&g, i_source, 10);

    println!(
        "{}",
        e0.into_iter().zip(e).map(|(x0, x)| x0 + x).sum::<u32>()
    )
}
