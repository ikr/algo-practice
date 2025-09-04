use proconio::input;
use proconio::marker::Chars;

fn main() {
    input! {
        xs: Chars,
    }

    let n = xs.len();
    let bolts = ['R', 'G', 'B'];
    let mut k: usize = 0;
    let mut result = 1;

    for (i, x) in xs.into_iter().enumerate() {
        if x != bolts[k] {
            k = (k + 1) % bolts.len();
            if i != n - 1 {
                result += 1;
            }
        }
    }

    println!("{result}");
}
