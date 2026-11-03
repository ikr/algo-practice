use std::{
    collections::{HashMap, HashSet},
    io::{BufRead, stdin},
};

fn decode_edges_source(s: String) -> (String, Vec<String>) {
    (
        s[..4].to_string(),
        s[5..].split(',').map(|a| a.to_string()).collect(),
    )
}

fn dfs(g: &HashMap<String, Vec<String>>, visited: &mut HashSet<String>, u: &str) {
    visited.insert(u.to_string());

    if let Some(vs) = g.get(u) {
        for v in vs {
            if !visited.contains(v) {
                dfs(g, visited, v);
            }
        }
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let g_inv: Vec<(String, Vec<String>)> = lines.into_iter().map(decode_edges_source).collect();

    let g: HashMap<String, Vec<String>> =
        g_inv.into_iter().fold(HashMap::new(), |mut agg, (u, vs)| {
            for v in vs {
                agg.entry(v)
                    .and_modify(|us| us.push(u.clone()))
                    .or_insert(vec![u.clone()]);
            }
            agg
        });

    let mut visited: HashSet<String> = HashSet::new();
    dfs(&g, &mut visited, "NULL");

    let result = visited.len() - 1;
    println!("{result}");
}
