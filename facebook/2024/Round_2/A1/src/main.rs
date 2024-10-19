use std::collections::BTreeSet;
use std::ops::Bound::Included;

use proconio::input;
use proconio_derive::fastout;

fn peak_num(k: u8, center: u8) -> u64 {
    assert!(center < 10);
    assert!(center > k);

    let pref: Vec<u8> = ((center - k)..center).map(|d| b'0' + d).collect();
    let suff: Vec<u8> = pref.iter().cloned().rev().collect();
    let bs: Vec<u8> = [pref, vec![center + b'0'], suff].concat();
    String::from_utf8(bs).unwrap().parse().unwrap()
}

fn all_peak_nums() -> BTreeSet<u64> {
    let mut result: BTreeSet<u64> = BTreeSet::new();
    for c in 1..10 {
        for k in 0..c {
            result.insert(peak_num(k, c));
        }
    }
    result
}

fn num_peaks(ps: &BTreeSet<u64>, a: u64, b: u64, m: u64) -> usize {
    ps.range((Included(&a), Included(&b)))
        .filter(|x| *x % m == 0)
        .count()
}

#[fastout]
fn main() {
    let ps = all_peak_nums();

    input! {
        cases_num: u16,
    }

    for t in 1..=cases_num {
        input! {
            a: u64,
            b: u64,
            m: u64
        }

        let result = num_peaks(&ps, a, b, m);
        println!("Case #{}: {}", t, result);
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn peak_num_works() {
        assert_eq!(peak_num(0, 9), 9);
        assert_eq!(peak_num(1, 2), 121);
        assert_eq!(peak_num(1, 6), 565);
        assert_eq!(peak_num(4, 5), 123454321);
        assert_eq!(peak_num(8, 9), 12345678987654321);
    }
}
