use std::collections::{BTreeSet, VecDeque};
use std::ops::Bound::Included;

use proconio::input;
use proconio_derive::fastout;

const MAX_B: u128 = 1_000_000_000 * 1_000_000_000;

fn num_from_source(xs: &VecDeque<u8>) -> u128 {
    String::from_utf8(xs.iter().map(|d| b'0' + d).collect::<Vec<_>>())
        .unwrap()
        .parse()
        .unwrap()
}

fn digits(mut n: u64) -> VecDeque<u8> {
    let mut result: VecDeque<u8> = VecDeque::new();
    while n != 0 {
        result.push_front((n % 10) as u8);
        n /= 10;
    }
    result
}

fn all_mountain_nums() -> BTreeSet<u64> {
    let mut result: BTreeSet<u64> = BTreeSet::new();
    let mut q: VecDeque<u64> = VecDeque::new();

    for d in 1..10 {
        let xs = VecDeque::from([d]);
        result.insert(num_from_source(&xs) as u64);
        q.push_back(d as u64);
    }

    while let Some(x0) = q.pop_front() {
        let xs0 = digits(x0);
        let a = xs0[0];
        let b = xs0.back().unwrap();
        let c = xs0[xs0.len() / 2];

        for aa in 1..=a {
            if aa == c {
                continue;
            }

            for bb in 1..=*b {
                if bb == c {
                    continue;
                }

                let mut xs = xs0.clone();
                xs.push_front(aa);
                xs.push_back(bb);
                if num_from_source(&xs) > MAX_B {
                    break;
                } else {
                    let x = num_from_source(&xs) as u64;
                    result.insert(x);
                    q.push_back(x);
                }
            }
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
    let ps = all_mountain_nums();

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
    fn num_from_source_works() {
        assert_eq!(num_from_source(&VecDeque::from([1])), 1);
        assert_eq!(num_from_source(&VecDeque::from([9, 9, 4])), 994);
    }

    #[test]
    fn digits_works() {
        assert_eq!(digits(31415), VecDeque::from([3, 1, 4, 1, 5]));
    }
}
