use std::collections::BTreeMap;

use proconio::input;

fn num_sought_pairs(m: i32, lrs: &[(i32, i32)]) -> i64 {
    let max_ls_by_r: BTreeMap<i32, i32> = lrs.iter().fold(BTreeMap::new(), |mut acc, (l, r)| {
        acc.entry(*r).and_modify(|x| *x = *l.max(x)).or_insert(*l);
        acc
    });

    let mut result: i64 = 0;

    for curr in 1..=m {
        let range = max_ls_by_r.range(..=curr);

        if let Some((r0, l0)) = range.last() {
            if !(*r0 == curr && l0 == r0) {
                result += (curr - l0) as i64;
            }
        } else {
            result += curr as i64;
        }
    }

    result
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
