use std::collections::BTreeMap;

use proconio::input;

fn num_sought_pairs(m: i32, lrs: &[(i32, i32)]) -> i64 {
    let max_ls_by_r: BTreeMap<i32, i32> = lrs.iter().fold(BTreeMap::new(), |mut acc, (l, r)| {
        acc.entry(*r).and_modify(|x| *x = *l.max(x)).or_insert(*l);
        acc
    });

    let mut dp: Vec<i64> = vec![0; (m + 1) as usize];

    for curr in 1..=m {
        let i = curr as usize;
        let range = max_ls_by_r.range(..=curr);

        if let Some((r0, l0)) = range.last() {
            if *r0 == curr {
                if l0 != r0 {
                    dp[i] = (curr - l0) as i64;
                }
            } else {
                dp[i] += dp[i - 1] + 1;
            }
        } else {
            dp[i] += dp[i - 1] + 1;
        }
    }

    dp.into_iter().sum()
}

fn main() {
    input! {
        n: usize,
        m: i32,
        lrs: [(i32, i32); n],
    }

    let result = num_sought_pairs(m, &lrs);
    println!("{}", result);
}
