use itertools::Itertools;
use rand::{Rng, rngs::ThreadRng};
use regex::Regex;
use std::{io::Read, iter::once};

const POPULATION_LIMIT: usize = 10_000;
const GENERATIONS: usize = 100;

fn decode_thickness(plant_source: &str) -> i64 {
    let re = Regex::new(r"^Plant (\d+) with thickness (-?\d+):").unwrap();
    let caps = re.captures(plant_source).unwrap();
    caps[2].parse().unwrap()
}

fn decode_edge(edge_source: &str) -> (usize, i64) {
    if edge_source.starts_with("- free branch") {
        let w = edge_source
            .strip_prefix("- free branch with thickness ")
            .unwrap()
            .parse()
            .unwrap();
        (0, w)
    } else {
        let re = Regex::new(r"^- branch to Plant (\d+) with thickness (-?\d+)$").unwrap();
        let caps = re.captures(edge_source).unwrap();
        let v: usize = caps[1].parse().unwrap();
        let w: i64 = caps[2].parse().unwrap();
        (v, w)
    }
}

fn graph_from_edges(num_vertices: usize, edges: Vec<Vec<(usize, i64)>>) -> Vec<Vec<(usize, i64)>> {
    let mut g = vec![vec![]; num_vertices];
    for (u, es) in edges.into_iter().enumerate() {
        for (v, w) in es {
            g[u.min(v)].push((u.max(v), w));
        }
    }
    g
}

fn decode_bools(zero_one_row: &str) -> Vec<bool> {
    zero_one_row.split(' ').map(|x| x == "1").collect()
}

fn decode_bool_matrix(zero_one_rows: &str) -> Vec<Vec<bool>> {
    zero_one_rows.split('\n').map(decode_bools).collect()
}

fn sinked_energy(
    g: &[Vec<(usize, i64)>],
    plant_thicknesses: &[i64],
    source_activations: &[bool],
) -> i64 {
    let n = plant_thicknesses.len();
    let mut flow_energy: Vec<i64> = vec![0; n];
    flow_energy[0] = 1;

    for (u, &(v, w)) in g[0].iter().enumerate() {
        if source_activations[u] {
            flow_energy[v] += flow_energy[0] * w;
        }
    }

    for u in 1..n {
        for &(v, w) in &g[u] {
            if flow_energy[u] >= plant_thicknesses[u] {
                flow_energy[v] += flow_energy[u] * w;
            }
        }
    }

    let sinked: i64 = *flow_energy.last().unwrap();

    if sinked >= *plant_thicknesses.last().unwrap() {
        sinked
    } else {
        0
    }
}

fn individuals_cross_over(rng: &mut ThreadRng, xs: Vec<bool>, ys: Vec<bool>) -> Vec<bool> {
    let m = xs.len();
    assert_eq!(ys.len(), m);
    let remaining_length: usize = rng.random_range(1..m);

    let mut result: Vec<bool> = xs[..remaining_length].to_vec();
    result.extend(&ys[remaining_length..]);
    assert_eq!(result.len(), m);
    result
}

fn random_individual(rng: &mut ThreadRng, m: usize) -> Vec<bool> {
    (0..m).map(|_| rng.random_bool(0.5)).collect()
}

fn next_generation(
    rng: &mut ThreadRng,
    g: &[Vec<(usize, i64)>],
    plant_thicknesses: &[i64],
    population: Vec<Vec<bool>>,
) -> Vec<Vec<bool>> {
    let m = population[0].len();

    let mut result: Vec<Vec<bool>> = population
        .into_iter()
        .tuple_combinations()
        .map(|(xs, ys)| individuals_cross_over(rng, xs, ys))
        .k_largest_by_key((POPULATION_LIMIT / 10) * 9, |xs| {
            sinked_energy(g, plant_thicknesses, xs)
        })
        .collect();

    while result.len() < POPULATION_LIMIT {
        result.push(random_individual(rng, m));
    }

    result
}

fn best_energy_in_population(
    g: &[Vec<(usize, i64)>],
    plant_thicknesses: &[i64],
    population: &[Vec<bool>],
) -> i64 {
    population
        .iter()
        .map(|xs| sinked_energy(g, plant_thicknesses, xs))
        .max()
        .unwrap()
}

fn main() {
    let mut buf: String = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();
    let isep = buf.find("\n\n\n").unwrap();

    let plant_sources: Vec<String> = buf[..isep]
        .trim_end()
        .split("\n\n")
        .map(|s| s.to_string())
        .collect();

    let plant_thicknesses: Vec<i64> = once(1)
        .chain(plant_sources.iter().map(|s| decode_thickness(s)))
        .collect();

    let edges: Vec<Vec<(usize, i64)>> = once(vec![])
        .chain(
            plant_sources
                .into_iter()
                .map(|s| s.split('\n').skip(1).map(decode_edge).collect()),
        )
        .collect();

    let activation_rows: Vec<Vec<bool>> = decode_bool_matrix(buf[isep + 3..].trim_end());
    eprintln!("Activation row length is {}", activation_rows[0].len());

    let n = plant_thicknesses.len();
    let g = graph_from_edges(n, edges);

    let es: Vec<i64> = activation_rows
        .iter()
        .filter_map(|source_activations| {
            let sub = sinked_energy(&g, &plant_thicknesses, source_activations);
            if sub == 0 { None } else { Some(sub) }
        })
        .collect();
    eprintln!("{:?} with max value of {}", es, es.iter().max().unwrap());

    let m = activation_rows[0].len();
    let mut rng = rand::rng();
    let mut population: Vec<Vec<bool>> = (0..n).map(|_| random_individual(&mut rng, m)).collect();
    let mut hi = 0;

    for t in 1..=GENERATIONS {
        population = next_generation(&mut rng, &g, &plant_thicknesses, population);
        let cur = best_energy_in_population(&g, &plant_thicknesses, &population);

        if cur > hi {
            hi = cur;

            let result: i64 = if es.iter().all(|&e| e <= hi) {
                es.iter().map(|&e| hi - e).sum()
            } else {
                0
            };

            println!("hi: {hi} in generation {t}, final result: {result}");
        }
    }
}
