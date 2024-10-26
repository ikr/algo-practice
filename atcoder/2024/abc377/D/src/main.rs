use itertools::Itertools;
use proconio::input;

fn num_sought_pairs(m: i64, lrs: &[(i64, i64)]) -> i64 {
    let mut containint_pairs: i64 = 0;

    for (l, r) in lrs {
        containint_pairs += l * (m - r + 1);
    }

    let total_pairs = m * (m + 1) / 2;
    total_pairs - containint_pairs
}

fn main() {
    input! {
        n: usize,
        m: i64,
        lrs: [(i64, i64); n],
    }

    let result = num_sought_pairs(m, &lrs.into_iter().unique().collect::<Vec<_>>());
    println!("{}", result);
}
