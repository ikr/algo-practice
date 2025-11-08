use itertools::Itertools;
use proconio::input;
use std::{
    collections::BTreeMap,
    io::{BufWriter, Write, stdout},
};

fn is_possible(hs: Vec<u32>, mut bs: BTreeMap<u32, usize>) -> bool {
    for h in hs {
        if let Some((&k, &v)) = bs.range(h..).last() {
            if v == 1 {
                bs.remove(&k);
            } else {
                bs.insert(k, v - 1);
            }
        } else {
            return false;
        }
    }

    true
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        m: usize,
        k: usize,
        hs: [u32; n],
        bs: [u32; m],
    }

    let result = if is_possible(
        hs.into_iter().k_smallest(k).rev().collect(),
        bs.into_iter().counts().into_iter().collect(),
    ) {
        "Yes"
    } else {
        "No"
    };
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
