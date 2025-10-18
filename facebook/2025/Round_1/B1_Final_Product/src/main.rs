use itertools::Itertools;
use proconio::input;
use proconio_derive::fastout;

fn multipliers(n: usize, a: u64, b: u64) -> Vec<u64> {
    let mut result = vec![1; n];
    result.push(b);
    result.extend(vec![1; n - 1]);
    result
}

#[fastout]
fn main() {
    input! {
        cases_num: u16,
    }

    for t in 1..=cases_num {
        input! {
            n: usize,
            a: u64,
            b: u64,
        }

        let result = multipliers(n, a, b).into_iter().join(" ");
        println!("Case #{t}: {result}");
    }
}
