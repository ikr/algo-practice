use regex::Regex;
use std::{io::Read, iter::once};

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

    let n = plant_thicknesses.len();
    let g = graph_from_edges(n, edges);
    let mut result = 0;

    for activations in activation_rows {
        let mut flow_energy: Vec<i64> = vec![0; n];
        flow_energy[0] = 1;

        for (u, &(v, w)) in g[0].iter().enumerate() {
            if activations[u] {
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

        result += if sinked >= *plant_thicknesses.last().unwrap() {
            sinked
        } else {
            0
        };
    }

    println!("{}", result);
}
