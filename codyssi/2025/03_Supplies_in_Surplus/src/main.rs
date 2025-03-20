use std::io::{self, BufRead};

fn parse_range(s: &str) -> (i32, i32) {
    let ab: Vec<i32> = s.split('-').map(|s| s.parse().unwrap()).collect();
    (ab[0], ab[1])
}

fn parse_line(s: &str) -> (i32, i32, i32, i32) {
    let ab: Vec<_> = s.split_ascii_whitespace().collect();
    let (a, b) = parse_range(ab[0]);
    let (c, d) = parse_range(ab[1]);
    (a, b, c, d)
}

fn intersection(ab: (i32, i32), cd: (i32, i32)) -> Option<(i32, i32)> {
    let (a, b) = ab;
    let (c, d) = cd;
    if b < c || d < a {
        None
    } else {
        let mut xs = [a, b, c, d];
        xs.sort();
        Some((xs[1], xs[2]))
    }
}

fn two_intersection_size(ab: (i32, i32), cd: (i32, i32)) -> i32 {
    if let Some((x, y)) = intersection(ab, cd) {
        y - x + 1
    } else {
        0
    }
}

fn three_intersection_size(ab: (i32, i32), cd: (i32, i32), ef: (i32, i32)) -> i32 {
    if let Some((x, y)) = intersection(ab, cd) {
        two_intersection_size((x, y), ef)
    } else if let Some((x, y)) = intersection(cd, ef) {
        two_intersection_size((x, y), ab)
    } else if let Some((x, y)) = intersection(ab, ef) {
        two_intersection_size((x, y), cd)
    } else {
        0
    }
}

fn four_union_size(ab: (i32, i32), cd: (i32, i32), ef: (i32, i32), gh: (i32, i32)) -> i32 {
    todo!()
}

fn main() {
    let lines: Vec<_> = io::stdin()
        .lock()
        .lines()
        .map(|s| parse_line(&s.unwrap()))
        .collect();

    let result: i32 = lines
        .into_iter()
        .map(|(a, b, c, d)| two_union_count((a, b), (c, d)))
        .sum();
    println!("{}", result);
}
