use std::io::Read;

const DISTANCE_LIMIT: usize = 1000;
const PATTERN_REPEATS: usize = 1000;

fn mentor_symbol(x: u8) -> u8 {
    x.to_ascii_uppercase()
}

fn is_novice_symbol(x: u8) -> bool {
    x.is_ascii_lowercase()
}

fn mentor_index(x: u8) -> usize {
    (x - b'A') as usize
}

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();
    let mut xs: Vec<u8> = vec![];

    for _ in 0..PATTERN_REPEATS {
        xs.extend(buf.trim().bytes())
    }

    let idx: Vec<Vec<usize>> = xs
        .iter()
        .enumerate()
        .filter(|(_, x)| !is_novice_symbol(**x))
        .fold(vec![vec![]; 3], |mut acc, (i, &x)| {
            acc[mentor_index(x)].push(i);
            acc
        });

    let result: usize = xs
        .into_iter()
        .enumerate()
        .filter(|(_, x)| is_novice_symbol(*x))
        .fold(0usize, |acc, (i, x)| {
            let k = mentor_index(mentor_symbol(x));
            let lo = i.saturating_sub(DISTANCE_LIMIT);
            let hi = i + DISTANCE_LIMIT;
            let a = idx[k].partition_point(|&j| j < lo);
            let b = idx[k].partition_point(|&j| j <= hi);
            acc + b - a
        });

    println!("{result}")
}
