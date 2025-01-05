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

fn snake_numers_up_to(hi: u64) -> u64 {
    todo!()
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
