use itertools::Itertools;
use proconio::input;
use std::{
    collections::BTreeMap,
    io::{BufWriter, Write, stdout},
};

fn max_sales(c: u64, aa: Vec<u64>, bb: Vec<u64>) -> u64 {
    let mut aa_fqs: BTreeMap<u64, usize> = aa.into_iter().counts().into_iter().collect();
    let mut result: u64 = 0;

    for b in bb.into_iter().rev() {
        if let Some((&a, &fq)) = aa_fqs.range(b..).next() {
            assert!(a >= b, "{a} isn't greater than {b}");
            assert_ne!(fq, 0);
            result += c;

            if fq == 1 {
                aa_fqs.remove(&b);
            } else {
                aa_fqs.insert(b, fq - 1);
            }
        }
    }

    result
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        m: usize,
        c: u64,
        aa: [u64; n],
        bb: [u64; m],
    }

    let result = max_sales(c, aa, bb);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
