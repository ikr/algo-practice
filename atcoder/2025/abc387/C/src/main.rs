use proconio::input;
use std::io::{self, BufWriter, Write};

fn digits(mut n: u64) -> Vec<u64> {
    let mut ans = vec![];
    while n != 0 {
        ans.push(n % 10);
        n /= 10;
    }
    ans.reverse();
    ans
}

fn count_k_digit_snake_numbers_starting_with_d0(k: usize, d0: u64) -> u64 {
    assert!(k > 1);
    assert_ne!(d0, 0);
    d0.pow(k as u32 - 1)
}

fn count_capped(ds: &[u64], d0: u64) -> u64 {
    assert_ne!(d0, 0);
    if ds.len() == 1 {
        d0.min(ds[0] + 1)
    } else {
        let mut result = 0;
        for _ in 1..ds[0].min(d0 - 1) {
            result += count_capped(&ds[1..], d0);
        }
        result
    }
}

fn snake_numers_up_to(hi: u64) -> u64 {
    if hi < 10 {
        0
    } else {
        let ds = digits(hi);
        let mut result = 0;

        for k in 2..ds.len() - 1 {
            for d0 in 1..10 {
                result += count_k_digit_snake_numbers_starting_with_d0(k, d0);
            }
        }

        for d0 in 1..ds[0] {
            result += count_k_digit_snake_numbers_starting_with_d0(ds.len(), d0);
        }

        result += count_capped(&ds[1..], ds[0]);
        result
    }
}

fn snake_numbers_within(l: u64, r: u64) -> u64 {
    snake_numers_up_to(r) - snake_numers_up_to(l - 1)
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        l:u64,
        r:u64
    }

    let result = snake_numbers_within(l, r);
    writeln!(writer, "{}", result).unwrap();
    writer.flush().unwrap();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn count_capped_works() {
        assert_eq!(count_capped(&[1, 0], 1), 1);
    }
}
