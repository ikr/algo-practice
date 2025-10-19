use ac_library::ModInt1000000007 as Mint;
use itertools::Itertools;
use primal::Sieve;
use proconio::input;
use proconio_derive::fastout;

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
            .map(|(i, &k0)| fb[i].0.pow(k0 as u32))
            .fold(1, |acc, x| acc * x);

        if aa > a {
            continue;
        }

        let total_exp_a: usize = ii.iter().sum();
        let lhs = Mint::new(n).pow(total_exp_a as u64);

        let kk: Vec<usize> = fb
            .iter()
            .enumerate()
            .map(|(i, &(_, k0))| {
                assert!(ii[i] <= k0);
                k0 - ii[i]
            })
            .collect();

        let total_exp_b: usize = kk.into_iter().sum();
        let rhs = Mint::new(n).pow(total_exp_b as u64);
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
