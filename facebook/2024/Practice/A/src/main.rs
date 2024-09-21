use proconio::input;
use proconio_derive::fastout;

fn can_cross_in_k_seconds(xs: &[u64], k: u64) -> bool {
    let n = xs.len() as u64;
    let lo = *xs.iter().min().unwrap();

    if n == 1 {
        lo <= k
    } else {
        let reg_tours = n - 2;
        let total_time = lo + 2 * reg_tours * lo;
        total_time <= k
    }
}

#[fastout]
fn main() {
    input! {
        cases_num: u16,
    }

    for t in 1..=cases_num {
        input! {
            n: usize,
            k: u64,
            xs: [u64; n],
        }

        let result = can_cross_in_k_seconds(&xs, k);
        println!("Case #{}: {}", t, if result { "YES" } else { "NO" });
    }
}
