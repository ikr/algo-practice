use proconio::input;
use proconio_derive::fastout;

fn suffix_maximums<T>(xs: &[T]) -> Vec<T>
where
    T: Clone,
    T: Copy,
    T: Ord,
{
    let n = xs.len();
    let mut result = vec![*xs.last().unwrap(); n];

    for i in (0..n - 1).rev() {
        result[i] = result[i + 1].max(xs[i]);
    }

    result
}

fn solve(xs: &[u32], g: u32) -> (usize, u32) {
    let suff_hi = suffix_maximums(xs);
    suff_hi
        .into_iter()
        .enumerate()
        .fold((usize::MAX, u32::MAX), |(i0, d0), (i, x)| {
            let d = g.abs_diff(x);

            if d < d0 {
                (i, d)
            } else {
                (i0, d0)
            }
        })
}

#[fastout]
fn main() {
    input! {
        cases_num: u16,
    }

    for t in 1..=cases_num {
        input! {
            n: usize,
            g: u32,
            xs: [u32; n],
        }

        let (i0, d) = solve(&xs, g);
        println!("Case #{}: {} {}", t, i0 + 1, d);
    }
}
