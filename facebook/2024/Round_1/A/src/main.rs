use std::cmp::Ordering;

use proconio::input;
use proconio_derive::fastout;

const Z: f64 = 0.00000001;
const EPS: f64 = 0.0000001;

fn preprocess_ab(ab: &[(i32, i32)]) -> Vec<(f64, f64)> {
    ab.iter()
        .map(|(a, b)| {
            let aa = (*a as f64).max(Z);
            let bb = *b as f64;
            (aa, bb)
        })
        .collect::<Vec<_>>()
}

fn intersection(ab: (f64, f64), cd: (f64, f64)) -> Option<(f64, f64)> {
    let (a, b) = ab;
    let (c, d) = cd;
    if b < c || d < a {
        None
    } else {
        let mut xs = [a, b, c, d];
        xs.sort_by(|a, b| {
            if (a - b).abs() < EPS {
                Ordering::Equal
            } else {
                a.partial_cmp(b).unwrap()
            }
        });
        Some((xs[1], xs[2]))
    }
}

fn min_speed(ab: Vec<(f64, f64)>) -> Option<f64> {
    let n = ab.len();
    let (last_a, last_b) = ab.last().unwrap();
    let last_d = n as f64;

    let mut lo = last_d / last_b;
    let mut hi = last_d / last_a;

    for i in (0..n - 1).rev() {
        let (a, b) = ab[i];

        let d = (i + 1) as f64;
        let cur_lo = d / b;
        let cur_hi = d / a;

        match intersection((lo, hi), (cur_lo, cur_hi)) {
            Some((x, y)) => {
                lo = x;
                hi = y;
            }
            None => {
                return None;
            }
        }
    }

    Some(lo)
}

#[fastout]
fn main() {
    input! {
        cases_num: u16,
    }

    for t in 1..=cases_num {
        input! {
            n: usize,
            ab: [(i32, i32); n],
        }

        match min_speed(preprocess_ab(&ab)) {
            Some(v) => println!("Case #{}: {:.7}", t, v),
            None => println!("Case #{}: -1", t),
        }
    }
}
