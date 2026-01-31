use proconio::input;
use std::{
    collections::BTreeSet,
    io::{BufWriter, Write, stdout},
};

fn is_satisfiable_in_m_ops(mut xs: Vec<u64>, mut m: u64) -> bool {
    let n = xs.len();

    let mut pq: BTreeSet<(u64, usize)> =
        (0..n - 1).map(|i| (xs[i].abs_diff(xs[i + 1]), i)).collect();

    while let Some((delta, j)) = pq.pop_last() {
        if delta <= 1 {
            return true;
        }

        if delta - 1 > m {
            return false;
        }

        assert!(j < n - 1);
        assert_eq!(xs[j].abs_diff(xs[j + 1]), delta);

        if xs[j] < xs[j + 1] {
            if j + 1 != n - 1 {
                pq.remove(&(xs[j + 1].abs_diff(xs[j + 2]), j + 1));
            }

            xs[j + 1] -= delta - 1;

            if j + 1 != n - 1 {
                pq.insert((xs[j + 1].abs_diff(xs[j + 2]), j + 1));
            }
        } else {
            if j != 0 {
                pq.remove(&(xs[j - 1].abs_diff(xs[j]), j - 1));
            }

            xs[j] -= delta - 1;

            if j != 0 {
                pq.insert((xs[j - 1].abs_diff(xs[j]), j - 1));
            }
        }

        pq.insert((xs[j].abs_diff(xs[j + 1]), j));
        m -= delta - 1;
    }

    false
}

fn min_ops(xs: Vec<u64>) -> u64 {
    let mut lo: u64 = 0;

    if is_satisfiable_in_m_ops(xs.clone(), lo) {
        return lo;
    }

    let mut hi: u64 = xs.len().pow(2) as u64;
    assert!(is_satisfiable_in_m_ops(xs.clone(), hi));

    while lo + 1 < hi {
        let mid = lo + (hi - lo) / 2;
        if is_satisfiable_in_m_ops(xs.clone(), mid) {
            hi = mid;
        } else {
            lo = mid;
        }
    }

    hi
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {t: u16}

    for _ in 0..t {
        input! {
            n: usize,
            xs: [u64; n],
        }

        let result = min_ops(xs);
        writeln!(writer, "{result}").unwrap();
    }

    writer.flush().unwrap();
}
