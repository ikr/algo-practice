use ac_library::ModInt1000000007 as Mint;
use itertools::Itertools;
use primal::Sieve;
use proconio::input;
use proconio_derive::fastout;

fn stars_and_bars_ways_num(s: usize, b: usize) -> Mint {
    let numerator = (0..s)
        .map(|addition| b + addition)
        .fold(Mint::new(1), |acc, x| acc * Mint::new(x));

    let denominator = (1..=s).fold(Mint::new(1), |acc, x| acc * Mint::new(x));
    numerator * denominator.inv()
}

fn sequences_num(sieve: &Sieve, n: usize, a: usize, b: usize) -> Mint {
    let fb = sieve.factor(b).unwrap();

    let exps_b: Vec<Vec<usize>> = fb
        .iter()
        .map(|(_, k)| (0..=*k).collect::<Vec<_>>())
        .collect();

    let mut result = Mint::new(0);

    for ii in exps_b.into_iter().multi_cartesian_product() {
        let aa: usize = ii
            .iter()
            .enumerate()
            .map(|(i, &k)| {
                assert!(k <= fb[i].1);
                fb[i].0.pow(k as u32)
            })
            .fold(1, |acc, x| acc * x);

        if aa > a {
            continue;
        }

        let lhs = ii
            .iter()
            .map(|&k| stars_and_bars_ways_num(k, n))
            .fold(Mint::new(1), |acc, x| acc * x);

        let kk: Vec<usize> = fb
            .iter()
            .enumerate()
            .map(|(i, &(_, k0))| {
                assert!(ii[i] <= k0);
                k0 - ii[i]
            })
            .collect();

        let rhs = kk
            .iter()
            .map(|&k| stars_and_bars_ways_num(k, n))
            .fold(Mint::new(1), |acc, x| acc * x);

        result += lhs * rhs;
    }

    result
}

#[fastout]
fn main() {
    let sieve = primal::Sieve::new(10_000_000);
    assert_eq!(sieve.factor(1).unwrap(), vec![]);

    input! {
        cases_num: u8,
    }

    for t in 1..=cases_num {
        input! {
            n: usize,
            a: usize,
            b: usize,
        }

        let result: u32 = sequences_num(&sieve, n, a, b).val();
        println!("Case #{t}: {result}");
    }
}
