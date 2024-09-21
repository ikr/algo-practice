use proconio::input;
use proconio_derive::fastout;

fn p_bump(n: i16, p: i8) -> f64 {
    let p0 = (p as f64) / 100.0;
    let p1 = p0 / p0.powf(1.0 / (n as f64));
    (p1 * 100.0) - (p0 * 100.0)
}

#[fastout]
fn main() {
    input! {
        cases_num: u16,
    }

    for t in 1..=cases_num {
        input! {
            n: i16,
            p: i8,
        }

        let result = p_bump(n, p);
        println!("Case #{}: {:.7}", t, result);
    }
}
