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

fn can_make_it(ab: &[(f64, f64)], v: f64) -> bool {
    for (i, (a, b)) in ab.iter().enumerate() {
        let d: f64 = (i + 1) as f64;
        let t = d / v;
        if t < *a || t > *b {
            return false;
        }
    }
    true
}

fn min_speed(ab: Vec<(f64, f64)>) -> Option<f64> {
    let n = ab.len();
    let xs = &ab[..n - 1];

    let (last_a, last_b) = ab.last().unwrap();
    let last_d = n as f64;

    let mut lo = last_d / last_b;
    if can_make_it(xs, lo) {
        return Some(lo);
    }

    let mut hi = last_d / last_a;
    if !can_make_it(xs, hi) {
        return None;
    }

    while hi - lo >= EPS {
        let mid = lo + (hi - lo) / 2.0;
        if can_make_it(xs, mid) {
            hi = mid;
        } else {
            lo = mid;
        }
    }

    Some(hi)
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
