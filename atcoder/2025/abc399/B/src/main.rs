use proconio::input;
use std::{
    collections::BTreeMap,
    io::{BufWriter, Write, stdout},
};

fn solve(xs: &[u8]) -> Vec<usize> {
    let mut idx: BTreeMap<u8, Vec<usize>> = BTreeMap::new();
    for (i, x) in xs.iter().enumerate() {
        idx.entry(*x).and_modify(|ii| ii.push(i)).or_insert(vec![i]);
    }

    let mut result: Vec<usize> = vec![0; xs.len()];
    let mut r: usize = 1;

    while let Some((_, ii)) = idx.pop_last() {
        let m = ii.len();
        for i in ii {
            result[i] = r;
        }
        r += m;
    }

    result
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        xs: [u8; n],
    }

    for r in solve(&xs) {
        writeln!(writer, "{}", r).unwrap();
    }
    writer.flush().unwrap();
}
