use std::io::{BufRead, stdin};

fn ltr_additive(xs0: &[u8]) -> Option<Vec<u8>> {
    let mut xs: Vec<u8> = xs0.to_vec();

    for i in 1..xs.len() {
        if xs[i - 1] > xs[i] {
            xs[i - 1] -= 1;
            xs[i] += 1;
        }
    }

    if xs == xs0 { None } else { Some(xs) }
}

fn ltr_subtractive(xs0: &[u8]) -> Option<Vec<u8>> {
    let mut xs = xs0.to_vec();

    for i in 1..xs.len() {
        if xs[i - 1] < xs[i] {
            xs[i - 1] += 1;
            xs[i] -= 1;
        }
    }

    if xs == xs0 { None } else { Some(xs) }
}

fn run_until_stable_return_rounds<F>(xs: Vec<u8>, rounds_cap: usize, round_f: F) -> (Vec<u8>, usize)
where
    F: Fn(&[u8]) -> Option<Vec<u8>>,
{
    let seq = (1..=rounds_cap).scan(xs, |acc, _| {
        if let Some(ys) = round_f(acc) {
            *acc = ys;
            Some(acc.clone())
        } else {
            None
        }
    });

    let (i, ys) = seq.enumerate().last().unwrap();
    (ys, i + 1)
}

fn checksum(xs: Vec<u8>) -> usize {
    xs.into_iter()
        .enumerate()
        .map(|(i, x)| (i + 1) * (x as usize))
        .sum()
}

fn main() {
    let xs: Vec<u8> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().parse().unwrap())
        .collect();

    let (ys, r0) = run_until_stable_return_rounds(xs, 10, ltr_additive);
    let (zs, _) = run_until_stable_return_rounds(ys, 10 - r0, ltr_subtractive);
    println!("{}", checksum(zs));
}
