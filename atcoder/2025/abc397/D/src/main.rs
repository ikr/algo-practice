use proconio::input;
use std::io::{self, BufWriter, Write};

const MIO: i128 = 1_000_000;
const BIO: i128 = MIO * 1000;

fn foo(d: i128, y: i128, n: i128) -> i128 {
    3 * d * y.pow(2) + 3 * d * d * y + d.pow(3) - n
}

fn sign(x: i128) -> i8 {
    if x == 0 {
        0
    } else if x < 0 {
        -1
    } else {
        1
    }
}

fn find_y(n: i128, d: i128) -> Option<i128> {
    let left_s = sign(foo(d, 1, n));
    if left_s == 0 {
        return Some(1);
    }

    let right_s = sign(foo(d, BIO, n));
    if right_s == 0 {
        return Some(BIO);
    }

    if left_s == right_s {
        return None;
    }

    let mut l = 1;
    let mut r = BIO;
    while l + 1 < r {
        let mid = l + (r - l) / 2;
        let mid_s = sign(foo(d, mid, n));
        if mid_s == 0 {
            return Some(mid);
        }

        if mid_s == left_s {
            l = mid;
        } else {
            r = mid;
        }
    }

    None
}

fn solve(n: i128) -> Option<(i128, i128)> {
    for d in 1..=MIO {
        if let Some(y) = find_y(n, d) {
            return Some((y + d, y));
        }
    }

    None
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: u64,
    }

    if let Some((x, y)) = solve(n as i128) {
        writeln!(writer, "{} {}", x, y).unwrap();
    } else {
        writeln!(writer, "-1").unwrap();
    }
    writer.flush().unwrap();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn isqrt_works() {
        assert_eq!(isqrt(10i128.pow(22)), Some(10i128.pow(11)));
        assert_eq!(isqrt(234245348979898i128.pow(2)), Some(234245348979898i128));
        assert_eq!(
            isqrt(234245348979898111i128.pow(2)),
            Some(234245348979898111i128)
        );
    }
}
