use itertools::Itertools;
use proconio::input;
use std::{
    collections::BTreeMap,
    io::{BufWriter, Write, stdout},
    usize,
};

fn prefix_sums(xs: Vec<usize>) -> Vec<usize> {
    xs.into_iter()
        .scan(0, |acc, x| {
            *acc += x;
            Some(*acc)
        })
        .collect()
}

fn sum_over_xi(m: usize, aa: Vec<usize>, c: usize) -> usize {
    let mut fq = aa
        .into_iter()
        .counts()
        .into_iter()
        .collect::<BTreeMap<_, _>>();

    if let Some(&f0) = fq.get(&0) {
        fq.remove(&0);
        fq.insert(usize::MAX, f0);
    }

    let xs: Vec<usize> = fq.values().cloned().chain(fq.values().cloned()).collect();
    let n = xs.len() / 2;
    let ss = prefix_sums(xs);

    let sigma = |i: usize, j: usize| -> usize {
        assert!(i <= j);
        assert!(j < ss.len());
        ss[j] - if i == 0 { 0 } else { ss[i - 1] }
    };

    let mut result = 0;

    for i in 0..n {
        let mut lo = sigma(i, i);
        if lo >= c {
            result += lo;
        } else {
            let mut hi = 2 * n - 1;
            assert!(sigma(i, hi) >= c);

            while lo + 1 != hi {
                let mid = lo + (hi - lo) / 2;
                if sigma(i, mid) >= c {
                    hi = mid;
                } else {
                    lo = mid;
                }
            }
            result += hi;
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
        c: usize,
        aa: [usize; n],
    }

    let result = sum_over_xi(m, aa, c);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
