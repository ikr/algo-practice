use std::io::{BufRead, stdin};

fn ltr_additive(xs0: &[u32]) -> Option<Vec<u32>> {
    let mut xs: Vec<u32> = xs0.to_vec();

    for i in 1..xs.len() {
        if xs[i - 1] > xs[i] {
            xs[i - 1] -= 1;
            xs[i] += 1;
        }
    }
    if xs == xs0 { None } else { Some(xs) }
}

fn ltr_subtractive(xs0: &[u32]) -> Option<Vec<u32>> {
    let mut xs = xs0.to_vec();

    for i in 1..xs.len() {
        if xs[i - 1] < xs[i] {
            xs[i - 1] += 1;
            xs[i] -= 1;
        }
    }
    if xs == xs0 { None } else { Some(xs) }
}

fn run_until_stable_return_rounds<F>(
    xs: Vec<u32>,
    rounds_cap: usize,
    round_f: F,
) -> (Vec<u32>, usize)
where
    F: Fn(&[u32]) -> Option<Vec<u32>>,
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

fn main() {
    let xs: Vec<u32> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().parse().unwrap())
        .collect();

    let cap: usize = 10_000_000;
    let (ys, r0) = run_until_stable_return_rounds(xs, cap, ltr_additive);
    assert!(r0 < cap);

    let (_, r1) = run_until_stable_return_rounds(ys, cap, ltr_subtractive);
    assert!(r1 < cap);

    println!("{}", r0 + r1);
}
