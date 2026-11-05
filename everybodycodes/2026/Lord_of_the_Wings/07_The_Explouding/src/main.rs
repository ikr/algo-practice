use itertools::Itertools;
use std::io::{BufRead, stdin};

//const ENERGY_THRESHOLD: u32 = u32::MAX; //100; //1_000_000;
//const EXPLOSION_IMPULSE: u32 = 10;
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
    let mut impulse_counts: Vec<u32> = vec![0; g.len()];
    impulse_counts[i_source] = 1;
    let mut strength: u32 = initial_impulse;
    let mut e = e0.to_vec();

    loop {
        let mut new_impulse_counts: Vec<u32> = vec![0; g.len()];
        eprintln!("strength:{strength} impulse_counts:{impulse_counts:?}");

        for (u, &m) in impulse_counts.iter().enumerate() {
            e[u] += m * strength;

            for &v in &g[u] {
                new_impulse_counts[v] += m;
            }
        }

        impulse_counts = new_impulse_counts;

        strength -= 1;

        if strength == 0 {
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

    let i_source: usize = 1;
    let e = simulate_clouds_return_energy(&g, &e0, i_source, INITIAL_IMPULSE);

    eprintln!("{e:?}");
    println!("{}", e.into_iter().sum::<u32>())
}
