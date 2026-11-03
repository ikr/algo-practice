use std::io::{BufRead, stdin};

fn decode_edges_source(s: String) -> (String, Vec<String>) {
    (
        s[..4].to_string(),
        s[5..].split(',').map(|a| a.to_string()).collect(),
    )
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let edges_sources: Vec<_> = lines.into_iter().map(decode_edges_source).collect();
    eprintln!("{edges_sources:?}");
}
