use proconio::input;
use proconio::marker::Bytes;
use proconio_derive::fastout;

fn solve(xs: &[u8]) -> bool {
    let a = xs.iter().filter(|x| **x == b'A').count();
    let b = xs.len() - a;
    a.abs_diff(b) == 1
}

#[fastout]
fn main() {
    input! {
        cases_num: u16,
    }

    for t in 1..=cases_num {
        input! {
            n: usize,
            xs: Bytes,
        }
        assert_eq!(xs.len(), n);

        let result = solve(&xs);
        println!("Case #{}: {}", t, if result { 'Y' } else { 'N' });
    }
}
