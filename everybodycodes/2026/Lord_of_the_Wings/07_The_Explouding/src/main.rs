use itertools::Itertools;
use std::{
    collections::{HashSet, VecDeque},
    io::{BufRead, stdin},
};

const ENERGY_THRESHOLD: u32 = 100; //1_000_000;
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

fn propagate_explosion(
    g: &[Vec<usize>],
    e: &mut Vec<u32>,
    exploded: &mut HashSet<usize>,
    u: usize,
    impulse: u32,
) {
    assert!(!exploded.contains(&u));
    e[u] += impulse;

    if e[u] >= ENERGY_THRESHOLD {
        explode(g, e, exploded, u);
    } else if impulse > 1 {
        for &v in &g[u] {
            if !exploded.contains(&v) {
                propagate_explosion(g, e, exploded, v, impulse - 1);
            }
        }
    }
}

fn explode(g: &[Vec<usize>], e: &mut Vec<u32>, exploded: &mut HashSet<usize>, u: usize) {
    assert!(!exploded.contains(&u));
    e[u] = 0;
    exploded.insert(u);

    for &v in &g[u] {
        if !exploded.contains(&v) {
            propagate_explosion(g, e, exploded, v, EXPLOSION_IMPULSE);
        }
    }
}

fn simulate_clouds_return_energy_and_all_exploded(
    g: &[Vec<usize>],
    i_source: usize,
    initial_impulse: u32,
) -> (Vec<u32>, HashSet<usize>) {
    let mut e: Vec<u32> = vec![0; g.len()];
    let mut q: VecDeque<(usize, u32)> = VecDeque::from([(i_source, initial_impulse)]);
    let mut exploded: HashSet<usize> = HashSet::new();

    while let Some((u, x)) = q.pop_front() {
        if exploded.contains(&u) {
            continue;
        }

        e[u] += x;

        if e[u] >= ENERGY_THRESHOLD {
            explode(g, &mut e, &mut exploded, u);
        } else if x > 1 {
            for &v in &g[u] {
                if !exploded.contains(&v) {
                    q.push_back((v, x - 1));
                }
            }
        }
    }

    for &u in &exploded {
        assert_eq!(e[u], 0);
    }

    (e, exploded)
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let decoded_lines: Vec<_> = lines.into_iter().map(decode_line).collect();
    let g: Vec<Vec<usize>> = decoded_lines.iter().map(|(_, vs)| vs.clone()).collect();
    let e0: Vec<u32> = decoded_lines.into_iter().map(|(x, _)| x).collect();

    let i_source: usize = 1;

    let (e, exploded) =
        simulate_clouds_return_energy_and_all_exploded(&g, i_source, INITIAL_IMPULSE);

    eprintln!("e:{e:?} exploded:{exploded:?}");

    println!(
        "{}",
        e0.into_iter()
            .enumerate()
            .zip(e)
            .filter_map(|((i, x0), x)| (!exploded.contains(&i)).then_some(x0 + x))
            .sum::<u32>()
    )
}
