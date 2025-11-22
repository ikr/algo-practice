use std::io::{BufRead, stdin};

fn ltr_additive_rounds_until_stable(mut xs: Vec<u64>) -> (Vec<u64>, u64) {
    let mut rounds: u64 = 0;

    loop {
        let mut cur: u64 = 0;

        for i in 1..xs.len() {
            if xs[i - 1] > xs[i] {
                let delta = (xs[i - 1] - xs[i]).div_ceil(2);
                cur = cur.max(delta);
                xs[i - 1] -= delta;
                xs[i] += delta;
            }
        }

        if cur == 0 {
            break;
        }
        rounds += cur;
    }

    (xs, rounds)
}

fn ltr_subtractive_rounds_until_stable(xs: Vec<u64>) -> u64 {
    let n: u64 = xs.len() as u64;
    let total: u64 = xs.iter().sum();
    assert_eq!(total % n, 0);
    let average = total / n;

    xs.into_iter()
        .filter_map(|x| if x > average { Some(x - average) } else { None })
        .sum()
}

fn ltr_additive(xs0: &[u64]) -> Option<Vec<u64>> {
    let mut xs: Vec<u64> = xs0.to_vec();

    for i in 1..xs.len() {
        if xs[i - 1] > xs[i] {
            xs[i - 1] -= 1;
            xs[i] += 1;
        }
    }
    if xs == xs0 { None } else { Some(xs) }
}

fn ltr_subtractive(xs0: &[u64]) -> Option<Vec<u64>> {
    let mut xs = xs0.to_vec();

    for i in 1..xs.len() {
        if xs[i - 1] < xs[i] {
            xs[i - 1] += 1;
            xs[i] -= 1;
        }
    }
    if xs == xs0 { None } else { Some(xs) }
}

fn run_until_stable_return_rounds<F>(xs: Vec<u64>, rounds_cap: usize, round_f: F) -> (Vec<u64>, u64)
where
    F: Fn(&[u64]) -> Option<Vec<u64>>,
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
    (ys, (i + 1) as u64)
}

fn main() {
    let xs: Vec<u64> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().parse().unwrap())
        .collect();

    // let (ys, r0) = run_until_stable_return_rounds(xs, 10_000_000, ltr_additive);
    // eprintln!("{:?} / {r0}", ys);
    //let (_, r1) = run_until_stable_return_rounds(ys, 10_000_000, ltr_subtractive);
    // let r1 = ltr_subtractive_rounds_until_stable(ys);
    // eprintln!("... / {r1}");
    // println!("{}", r0 + r1);

    assert!(xs.is_sorted());
    println!("{}", ltr_subtractive_rounds_until_stable(xs));
}
