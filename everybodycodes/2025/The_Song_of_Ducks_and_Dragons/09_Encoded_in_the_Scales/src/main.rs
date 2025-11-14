use ac_library::Dsu;
use itertools::{Itertools, izip};
use std::io::{BufRead, stdin};

fn parse_line(s: &str) -> Vec<u8> {
    s.split(':').collect::<Vec<_>>()[1].bytes().collect()
}

fn is_child_of_ab(a: &[u8], b: &[u8], c: &[u8]) -> bool {
    izip!(a, b, c).all(|(x, y, z)| z == x || z == y)
}

fn maybe_edges(
    xss: &[Vec<u8>],
    ijk: (usize, usize, usize),
) -> Option<((usize, usize), (usize, usize))> {
    let (i, j, k) = ijk;

    [(i, j, k), (j, k, i), (i, k, j)]
        .into_iter()
        .find(|&(i, j, k)| is_child_of_ab(&xss[i], &xss[j], &xss[k]))
        .map(|(i, j, k)| ((i, j), (j, k)))
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let xss: Vec<Vec<u8>> = lines.into_iter().map(|s| parse_line(&s)).collect();
    let n = xss.len();

    let mut dsu = (0..n)
        .tuple_combinations()
        .fold(Dsu::new(n), |mut acc, (i, j, k)| {
            if let Some(((a, b), (c, d))) = maybe_edges(&xss, (i, j, k)) {
                acc.merge(a, b);
                acc.merge(c, d);
            }
            acc
        });

    let largest_family: Vec<usize> = dsu
        .groups()
        .into_iter()
        .max_by_key(|g| g.len())
        .unwrap()
        .iter()
        .map(|i| i + 1)
        .collect();

    let result: usize = largest_family.into_iter().sum();
    println!("{result}");
}
