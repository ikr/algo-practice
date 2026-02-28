use itertools::Itertools;
use proconio::input;
use std::{
    cmp::Reverse,
    collections::BTreeMap,
    io::{BufWriter, Write, stdout},
};

fn max_sales(c: u64, aa: Vec<u64>, bb: Vec<u64>) -> u64 {
    let mut bb_fqs: BTreeMap<Reverse<u64>, usize> = bb
        .into_iter()
        .counts()
        .into_iter()
        .map(|(k, fq)| (Reverse(k), fq))
        .collect();

    let mut result: u64 = 0;

    for a in aa {
        if let Some((&Reverse(b), &fq)) = bb_fqs.range(Reverse(a)..).next() {
            assert!(a >= b, "{a} isn't greater than {b}");
            assert_ne!(fq, 0);
            result += c;

            if fq == 1 {
                bb_fqs.remove(&Reverse(b));
            } else {
                bb_fqs.insert(Reverse(b), fq - 1);
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
