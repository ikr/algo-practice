use proconio::input;
use std::{
    collections::{HashSet, VecDeque},
    io::{BufWriter, Write, stdout},
};

fn index_flood_fill_from_minimums(xs: &[u64]) -> Vec<usize> {
    let n = xs.len();
    let lo: u64 = *xs.iter().min().unwrap();
    let mut q: VecDeque<usize> = (0..n).filter(|&i| xs[i] == lo).collect();
    let mut result: Vec<_> = q.iter().cloned().collect();
    let mut done: HashSet<usize> = q.iter().cloned().collect();

    while let Some(i) = q.pop_front() {
        if i != 0 && !done.contains(&(i - 1)) {
            result.push(i - 1);
            q.push_back(i - 1);
            done.insert(i - 1);
        }

        if i != n - 1 && !done.contains(&(i + 1)) {
            result.push(i + 1);
            q.push_back(i + 1);
            done.insert(i + 1);
        }
    }

    assert_eq!(result.len(), n);
    assert_eq!(done.len(), n);
    result
}

fn is_satisfiable_in_k_ops(iq: &[usize], mut xs: Vec<u64>, mut k: u64) -> bool {
    let n = xs.len();

    for &i in iq {
        let lhs: u64 = if i == 0 { xs[i] } else { xs[i - 1] };
        let rhs: u64 = if i == n - 1 { xs[i] } else { xs[i + 1] };
        let lo = lhs.min(xs[i]).min(rhs);

        if xs[i] - lo > 1 {
            let ops = xs[i] - lo - 1;

            if ops > k {
                return false;
            }

            xs[i] -= ops;
            k -= ops;
        }
    }

    true
}

fn min_ops(xs: Vec<u64>) -> u64 {
    let iq = index_flood_fill_from_minimums(&xs);
    let mut lo: u64 = 0;

    if is_satisfiable_in_k_ops(&iq, xs.clone(), lo) {
        return lo;
    }

    let mut hi: u64 = xs.len().pow(2) as u64;
    assert!(is_satisfiable_in_k_ops(&iq, xs.clone(), hi));

    while lo + 1 < hi {
        let mid = lo + (hi - lo) / 2;
        if is_satisfiable_in_k_ops(&iq, xs.clone(), mid) {
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
