use std::io::{self, BufRead};

const M: u64 = 16777216;

fn evolve(mut x: u64) -> u64 {
    let a = x * 64;
    x = (x ^ a) % M;
    let c = x / 32;
    x = (x ^ c) % M;
    let e = x * 2048;
    x = (x ^ e) % M;
    x
}

fn evolve_2000(mut x: u64) -> u64 {
    for _ in 0..2000 {
        x = evolve(x);
    }
    x
}

fn banana_windows(xs: &[u64]) -> Vec<(i8, [i8; 4])> {
    let deltas: Vec<i8> = xs
        .windows(2)
        .map(|ab| {
            let a = (ab[0] % 10) as i8;
            let b = (ab[1] % 10) as i8;
            b - a
        })
        .collect();

    let xds: Vec<(i8, i8)> = xs[1..]
        .iter()
        .zip(deltas.into_iter())
        .map(|(&x, d)| ((x % 10) as i8, d))
        .collect();

    xds.windows(4)
        .map(|pquad| {
            let last_x = pquad.last().unwrap().0;
            let ds = pquad.iter().map(|(_, d)| *d).collect::<Vec<_>>();
            (last_x, ds.try_into().unwrap())
        })
        .collect()
}

fn main() {
    let xs: Vec<u64> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().parse().unwrap())
        .collect();

    println!("{}", xs.into_iter().map(evolve_2000).sum::<u64>());

    let ys: Vec<u64> = vec![
        123, 15887950, 16495136, 527345, 704524, 1553684, 12683156, 11100544, 12249484, 7753432,
    ];

    eprintln!("{:?}", banana_windows(&ys));
}
