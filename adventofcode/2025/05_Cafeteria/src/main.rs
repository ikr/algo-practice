use std::io::{BufRead, stdin};

fn decode_range(s: &str) -> (u64, u64) {
    let parts = s.split('-').collect::<Vec<_>>();
    (parts[0].parse().unwrap(), parts[1].parse().unwrap())
}

fn are_overlapping(ab: (u64, u64), cd: (u64, u64)) -> bool {
    let ((a, b), (c, d)) = (ab, cd);
    !(d < a || b < c)
}

fn overlapping_union(ab: (u64, u64), cd: (u64, u64)) -> (u64, u64) {
    let ((a, b), (c, d)) = (ab, cd);
    (a.min(c), b.max(d))
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let isep = lines.iter().position(|s| s.is_empty()).unwrap();
    let ranges: Vec<(u64, u64)> = lines[..isep].iter().map(|s| decode_range(s)).collect();

    let mut disjoint: Vec<(u64, u64)> = vec![];

    for ab in ranges {
        let mut cur: (u64, u64) = ab;

        while let Some(i) = disjoint.iter().position(|&cd| are_overlapping(cur, cd)) {
            let ab: (u64, u64) = disjoint[i];
            disjoint.remove(i);
            cur = overlapping_union(cur, ab);
        }

        disjoint.push(cur);
    }

    let result: u64 = disjoint.into_iter().map(|(a, b)| b - a + 1).sum();
    println!("{result}");
}
