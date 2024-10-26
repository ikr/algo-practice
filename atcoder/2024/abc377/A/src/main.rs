use proconio::input;
use proconio::marker::Bytes;

fn solve(mut xs: Vec<u8>) -> bool {
    xs.sort();
    xs == b"ABC"
}

fn main() {
    input! {
        xs: Bytes,
    }
    let result = solve(xs);
    println!("{}", if result { "Yes" } else { "No" });
}
