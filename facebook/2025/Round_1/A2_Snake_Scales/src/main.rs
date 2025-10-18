use proconio::input;
use proconio_derive::fastout;

fn shortest_ladder_height(xs: Vec<u32>) -> u32 {
    let n = xs.len();
    let lo = xs[0];
    let mut up: Vec<u32> = vec![lo; n];
    let mut gr: Vec<u32> = vec![lo; n];

    for i in 1..n {
        up[i] = xs[i - 1].abs_diff(xs[i]).max(gr[i - 1].min(up[i - 1]));
        gr[i] = xs[i].max(gr[i - 1].min(up[i - 1]));
    }

    up[n - 1].min(gr[n - 1])
}

#[fastout]
fn main() {
    input! {
        cases_num: u16,
    }

    for t in 1..=cases_num {
        input! {
            n: usize,
            xs: [u32; n],
        }

        let result = shortest_ladder_height(xs);
        println!("Case #{t}: {result}");
    }
}
