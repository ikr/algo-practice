use std::collections::HashSet;

use primal::Primes;
use proconio::input;
use proconio_derive::fastout;

const N: usize = 10_000_000;

#[fastout]
fn main() {
    let ps = Primes::all().take_while(|p| *p < N).collect::<Vec<_>>();
    let pss: HashSet<usize> = ps.iter().cloned().collect();
    assert_eq!(ps[0], 2);

    let mut dp: Vec<usize> = vec![0; ps.len()];
    dp[2] = 2;

    for i in 3..dp.len() {
        let p = ps[i];
        if pss.contains(&(p - 2)) {
            dp[i] = dp[i - 1] + 1;
        } else {
            dp[i] = dp[i - 1];
        }
    }

    input! {
        cases_num: u16,
    }

    for t in 1..=cases_num {
        input! {
            n: usize,
        }

        let result: usize = match ps.binary_search(&n) {
            Ok(i) => dp[i],
            Err(i) => {
                if i == 0 {
                    0
                } else {
                    dp[i - 1]
                }
            }
        };

        println!("Case #{}: {}", t, result);
    }
}
