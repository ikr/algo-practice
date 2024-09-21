use proconio::input;
use proconio_derive::fastout;

fn solve(xs: &[u32], g: u32) -> (usize, u32) {
    todo!()
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
