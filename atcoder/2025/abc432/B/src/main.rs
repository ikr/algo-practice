use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn digits_reversed(mut x: u32) -> Vec<u32> {
    if x == 0 {
        return vec![0];
    }

    let mut ans = vec![];
    while x != 0 {
        ans.push(x % 10);
        x /= 10;
    }
    ans
}

fn number(ds: Vec<u32>) -> u32 {
    if ds.is_empty() {
        0
    } else {
        let mut ans = 0;
        let mut mul = 1;

        for d in ds.into_iter().rev() {
            ans += d * mul;
            mul *= 10;
        }

        ans
    }
}

fn min_arrangement_of_digits(x0: u32) -> u32 {
    let mut ds = digits_reversed(x0);
    let i0: usize = ds
        .iter()
        .enumerate()
        .filter(|(_, d)| **d != 0)
        .min_by_key(|(_, d)| **d)
        .unwrap()
        .0;
    let first_digit = ds[i0];
    ds.remove(i0);
    ds.sort();
    ds.insert(0, first_digit);
    number(ds)
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        x: u32,
    }

    let result = min_arrangement_of_digits(x);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
