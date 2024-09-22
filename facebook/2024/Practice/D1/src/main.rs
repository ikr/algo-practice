use proconio::input;
use proconio_derive::fastout;

fn solve(mut xs: Vec<u32>, g: u32) -> (usize, u32) {
    let n = xs.len();
    xs.sort();

    (0..n).rev().fold((usize::MAX, u32::MAX), |(i0, d0), j| {
        let i = n - 1 - j;
        let x = xs[j];
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

        let (i0, d) = solve(xs, g);
        println!("Case #{}: {} {}", t, i0 + 1, d);
    }
}
