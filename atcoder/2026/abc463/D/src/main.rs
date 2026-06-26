use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn is_k_gap_g_possible(lrs: &[(u32, u32)], k: usize, g: u32) -> bool {
    let (_, sz) = lrs
        .iter()
        .skip(1)
        .fold((lrs[0].1, 1), |(edge, n), &(l, r)| {
            if edge + g <= l { (r, n + 1) } else { (edge, n) }
        });

    sz >= k
}

fn lowest_k_gap(lrs: &[(u32, u32)], k: usize) -> Option<u32> {
    let mut lo: u32 = 1;
    if !is_k_gap_g_possible(lrs, k, lo) {
        return None;
    }

    let mut hi: u32 = 1_000_000_007;
    assert!(!is_k_gap_g_possible(lrs, k, hi));

    while lo + 1 != hi {
        let mid = lo + (hi - lo) / 2;
        if is_k_gap_g_possible(lrs, k, mid) {
            lo = mid;
        } else {
            hi = mid;
        }
    }

    Some(lo)
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        k: usize,
        mut lrs: [(u32, u32); n],
    }

    lrs.sort_by_key(|&(_, r)| r);

    let result = match lowest_k_gap(&lrs, k) {
        Some(a) => a.to_string(),
        None => "-1".to_string(),
    };
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
