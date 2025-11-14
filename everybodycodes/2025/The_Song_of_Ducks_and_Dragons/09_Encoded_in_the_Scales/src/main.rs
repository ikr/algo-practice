use itertools::izip;
use std::io::{BufRead, stdin};

fn parse_line(s: &str) -> Vec<u8> {
    s.split(':').collect::<Vec<_>>()[1].bytes().collect()
}

fn is_child_of_ab(a: &[u8], b: &[u8], c: &[u8]) -> bool {
    izip!(a, b, c).all(|(x, y, z)| z == x || z == y)
}

fn degree_of_similarity(xs: &[u8], ys: &[u8]) -> usize {
    xs.iter()
        .zip(ys)
        .map(|(x, y)| if x == y { 1 } else { 0 })
        .sum()
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let xss: Vec<Vec<u8>> = lines.into_iter().map(|s| parse_line(&s)).collect();

    for (i, j, k) in [(0, 1, 2), (1, 2, 0), (0, 2, 1)] {
        if is_child_of_ab(&xss[i], &xss[j], &xss[k]) {
            let da = degree_of_similarity(&xss[i], &xss[k]);
            let db = degree_of_similarity(&xss[j], &xss[k]);
            println!("da:{da} db:{db} -> {}", da * db);
        }
    }
}
