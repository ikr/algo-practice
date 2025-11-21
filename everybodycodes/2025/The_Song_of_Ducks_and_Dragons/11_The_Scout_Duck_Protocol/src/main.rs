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

fn ltr_subtractive_rounds_until_stable(mut xs: Vec<u64>) -> u64 {
    let mut rounds: u64 = 0;

    loop {
        let mut cur: u64 = 0;

        for i in 1..xs.len() {
            if xs[i] > xs[i - 1] {
                let delta = (xs[i] - xs[i - 1]).div_ceil(2);
                cur = cur.max(delta);
                xs[i - 1] += delta;
                xs[i] -= delta;
            }
        }

        if cur == 0 {
            break;
        }
        eprintln!("{:?} / {cur}", xs);
        rounds += cur;
    }

    rounds
}

fn main() {
    let xs: Vec<u64> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().parse().unwrap())
        .collect();

    let (ys, r0) = ltr_additive_rounds_until_stable(xs);
    eprintln!("{:?} / {r0}", ys);
    let r1 = ltr_subtractive_rounds_until_stable(ys);
    eprintln!("... / {r1}");
    println!("{}", r0 + r1);
}
