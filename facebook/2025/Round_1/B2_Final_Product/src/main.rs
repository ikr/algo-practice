use ac_library::ModInt1000000007 as Mint;
use itertools::Itertools;
use primal::Sieve;
use proconio::input;
use proconio_derive::fastout;

fn capped_factors(sieve: &Sieve, x: usize, cap: &[(usize, usize)]) -> Vec<(usize, usize)> {
    let prime_index = |p: usize| -> Option<usize> { cap.iter().position(|(q, _)| *q == p) };
    let ff = sieve.factor(x).unwrap();

    let result = ff
        .into_iter()
        .filter_map(|(p, i0)| {
            if let Some(j) = prime_index(p) {
                let i = i0.min(cap[j].1);
                Some((p, i))
            } else {
                None
            }
        })
        .collect::<Vec<_>>();

    if result.is_empty() {
        vec![(1, 0)]
    } else {
        result
    }
}

fn sequences_num(sieve: &Sieve, n: usize, a: usize, b: usize) -> Mint {
    let fb = sieve.factor(b).unwrap();
    let fa = capped_factors(sieve, a, &fb);
    eprintln!("n: {n}, a: {a}, b: {b}, fa: {:?}, fb: {:?}", fa, fb);

    let exps_a: Vec<Vec<usize>> = fa
        .iter()
        .map(|(_, k)| (0..=*k).collect::<Vec<_>>())
        .collect();

    let mut result = Mint::new(0);

    for ii in exps_a.into_iter().multi_cartesian_product() {
        let total_exp_a: usize = ii.iter().sum();
        let lhs_placements_num = Mint::new(n).pow(total_exp_a as u64);
        let a_prime_index = |p: usize| -> Option<usize> { fa.iter().position(|(q, _)| *q == p) };

        let kk: Vec<usize> = fb
            .iter()
            .map(|&(p, k0)| {
                if let Some(i) = a_prime_index(p) {
                    assert!(ii[i] <= k0);
                    k0 - ii[i]
                } else {
                    k0
                }
            })
            .collect();

        let total_exp_b: usize = kk.into_iter().sum();
        let rhs_placements_num = Mint::new(n).pow(total_exp_b as u64);
        eprintln!(
            "lhs: {}, rhs: {}",
            lhs_placements_num.val(),
            rhs_placements_num.val()
        );
        result += lhs_placements_num * rhs_placements_num;
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
