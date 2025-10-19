use ac_library::ModInt1000000007 as Mint;
use primal::Sieve;
use proconio::input;
use proconio_derive::fastout;

fn capped_factors(sieve: &Sieve, x: usize, cap: &[(usize, usize)]) -> Vec<(usize, usize)> {
    let prime_index = |p: usize| -> Option<usize> { cap.iter().position(|(q, _)| *q == p) };
    let ff = sieve.factor(x).unwrap();

    ff.into_iter()
        .filter_map(|(p, i0)| {
            if let Some(j) = prime_index(p) {
                let i = i0.min(cap[j].1);
                Some((p, i))
            } else {
                None
            }
        })
        .collect()
}

fn sequences_num(sieve: &Sieve, n: usize, a: usize, b: usize) -> Mint {
    let fb = sieve.factor(b).unwrap();
    let fa = capped_factors(sieve, a, &fb);
    todo!()
}

#[fastout]
fn main() {
    let sieve = primal::Sieve::new(10_000_000);
    assert_eq!(sieve.factor(1).unwrap(), vec![]);

    input! {
        cases_num: u16,
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
