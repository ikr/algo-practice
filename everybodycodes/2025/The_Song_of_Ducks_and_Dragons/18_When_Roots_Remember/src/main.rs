use regex::Regex;
use std::{io::Read, iter::once};

fn decode_thickness(plant_source: &str) -> u64 {
    let re = Regex::new(r"^Plant (\d+) with thickness (\d+):").unwrap();
    let caps = re.captures(plant_source).unwrap();
    caps[2].parse().unwrap()
}

fn decode_edge(edge_source: &str) -> (usize, u64) {
    if edge_source.starts_with("- free branch") {
        let w = edge_source
            .strip_prefix("- free branch with thickness ")
            .unwrap()
            .parse()
            .unwrap();
        (0, w)
    } else {
        let re = Regex::new(r"^- branch to Plant (\d+) with thickness (\d+)$").unwrap();
        let caps = re.captures(edge_source).unwrap();
        let v: usize = caps[1].parse().unwrap();
        let w: u64 = caps[2].parse().unwrap();
        (v, w)
    }
}

fn graph_from_edges(num_vertices: usize, edges: Vec<Vec<(usize, u64)>>) -> Vec<Vec<(usize, u64)>> {
    let mut g = vec![vec![]; num_vertices];
    for (u, es) in edges.into_iter().enumerate() {
        for (v, w) in es {
            g[u.min(v)].push((u.max(v), w));
        }
    }
    g
}

fn main() {
    let mut buf: String = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();

    let plant_sources: Vec<String> = buf
        .trim_end()
        .split("\n\n")
        .map(|s| s.to_string())
        .collect();

    let plant_thicknesses: Vec<u64> = once(1)
        .chain(plant_sources.iter().map(|s| decode_thickness(s)))
        .collect();

    let edges: Vec<Vec<(usize, u64)>> = once(vec![])
        .chain(plant_sources.into_iter().map(|s| {
            s.split('\n')
                .skip(1)
                .map(|line| decode_edge(line))
                .collect()
        }))
        .collect();

    let g = graph_from_edges(plant_thicknesses.len(), edges);
    eprintln!("{:?}", g);
}
