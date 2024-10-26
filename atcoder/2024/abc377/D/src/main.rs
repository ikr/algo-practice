use std::collections::{BTreeMap, BTreeSet, BinaryHeap};

use itertools::Itertools;
use proconio::input;

fn num_sought_pairs(m: i64, lrs: &[(i64, i64)]) -> i64 {
    let mut ops: BTreeMap<i64, Vec<usize>> = BTreeMap::new();
    let mut cls: BTreeMap<i64, Vec<usize>> = BTreeMap::new();
    let mut mss: BTreeSet<i64> = BTreeSet::new();

    for (i, (l, r)) in lrs.iter().enumerate() {
        ops.entry(*l)
            .and_modify(|indices| indices.push(i))
            .or_insert(vec![i]);
        cls.entry(*r)
            .and_modify(|indices| indices.push(i))
            .or_insert(vec![i]);
        mss.insert(*l);
        mss.insert(*r);
    }

    let mut currently_open: BinaryHeap<(i64, usize)> = BinaryHeap::new();

    let mut result = m * (m + 1) / 2;
    result
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
