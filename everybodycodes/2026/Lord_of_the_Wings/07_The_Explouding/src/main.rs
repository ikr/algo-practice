use itertools::Itertools;
use std::{
    collections::{HashMap, HashSet},
    io::{BufRead, stdin},
};

const ENERGY_THRESHOLD: u32 = 1_000_000;
const EXPLOSION_IMPULSE: u32 = 10;
const INITIAL_IMPULSE: u32 = 10;

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
    e0: &[u32],
    i_source: usize,
    initial_impulse: u32,
) -> Vec<u32> {
    let mut impulse_counts_by_strength: Vec<HashMap<u32, u32>> = vec![HashMap::new(); g.len()];
    impulse_counts_by_strength[i_source].insert(initial_impulse, 1);
    let mut e = e0.to_vec();
    let mut exploded: HashSet<usize> = HashSet::new();

    loop {
        let mut new_counts_by_strength: Vec<HashMap<u32, u32>> = vec![HashMap::new(); g.len()];

        for u in 0..g.len() {
            if exploded.contains(&u) {
                continue;
            }

            for (strength, m) in &impulse_counts_by_strength[u] {
                e[u] += m * strength;
            }

            if e[u] >= ENERGY_THRESHOLD {
                e[u] = 0;
                exploded.insert(u);
                new_counts_by_strength[u].clear();

                for &v in &g[u] {
                    if !exploded.contains(&v) {
                        new_counts_by_strength[v]
                            .entry(EXPLOSION_IMPULSE)
                            .and_modify(|k| *k += 1)
                            .or_insert(1);
                    }
                }
            }
            for &v in &g[u] {
                for (&strength, &m) in &impulse_counts_by_strength[u] {
                    if strength != 0 && !exploded.contains(&v) {
                        new_counts_by_strength[v]
                            .entry(strength - 1)
                            .and_modify(|k| *k += m)
                            .or_insert(m);
                    }
                }
            }
        }

        impulse_counts_by_strength = new_counts_by_strength;

        if impulse_counts_by_strength.iter().all(|cbs| cbs.is_empty()) {
            break;
        }
    }

    e
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let decoded_lines: Vec<_> = lines.into_iter().map(decode_line).collect();
    let g: Vec<Vec<usize>> = decoded_lines.iter().map(|(_, vs)| vs.clone()).collect();
    let e0: Vec<u32> = decoded_lines.into_iter().map(|(x, _)| x).collect();

    let result = (0..g.len())
        .map(|i_source| {
            let e = simulate_clouds_return_energy(&g, &e0, i_source, INITIAL_IMPULSE);
            e.into_iter().sum::<u32>()
        })
        .max()
        .unwrap();

    println!("{result}");
}
