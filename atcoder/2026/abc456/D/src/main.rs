use ac_library::ModInt998244353 as Mint;
use itertools::Itertools;
use proconio::input;
use proconio::marker::Bytes;
use std::io::{BufWriter, Write, stdout};

fn other_than_k(xs: Vec<usize>, k: usize) -> Vec<usize> {
    xs.into_iter().filter(|&x| x != k).collect()
}

fn num_good_subsequences(xs: Vec<usize>) -> Mint {
    // dp[i] is the number of good sub-sequences ending with i, exactly at the "current" index
    let mut dp = [Mint::new(0); 3];
    let mut result = Mint::new(1);
    dp[xs[0]] = Mint::new(1);

    for &i in &xs[1..] {
        let (i1, i2) = other_than_k(vec![0, 1, 2], i)
            .into_iter()
            .collect_tuple()
            .unwrap();

        let sub = Mint::new(1) + dp[i1] + dp[i2];
        dp[i] += sub;
        result += sub;
    }

    result
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
