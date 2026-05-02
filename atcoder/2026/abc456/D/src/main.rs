use ac_library::ModInt998244353 as Mint;
use proconio::input;
use proconio::marker::Bytes;
use std::io::{BufWriter, Write, stdout};

fn num_good_subsequences(xs: Vec<usize>) -> Mint {
    let mut dp = [Mint::new(0), Mint::new(0), Mint::new(0)];
    dp[xs[0]] = Mint::new(1);

    for x in xs.into_iter().skip(1) {}
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        xs: Bytes,
    }

    let result = num_good_subsequences(xs.into_iter().map(|x| (x - b'a') as usize).collect());
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
