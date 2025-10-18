use proconio::input;
use proconio_derive::fastout;

fn shortest_ladder_height(xs: Vec<i32>) -> i32 {
    if xs.len() == 1 {
        return 0;
    }

    xs.windows(2)
        .map(|xy| {
            let x = xy[0];
            let y = xy[1];
            x.abs_diff(y) as i32
        })
        .max()
        .unwrap()
}

#[fastout]
fn main() {
    input! {
        cases_num: u16,
    }

    for t in 1..=cases_num {
        input! {
            n: usize,
            xs: [i32; n],
        }

        let result = shortest_ladder_height(xs);
        println!("Case #{t}: {result}");
    }
}
