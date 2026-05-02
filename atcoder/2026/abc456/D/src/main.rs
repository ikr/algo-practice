use ac_library::ModInt998244353 as Mint;
use itertools::Itertools;
use proconio::input;
use proconio::marker::Bytes;
use std::io::{BufWriter, Write, stdout};

fn other_than_k(xs: Vec<usize>, k: usize) -> Vec<usize> {
    xs.into_iter().filter(|&x| x != k).collect()
}

fn num_good_subsequences(xs: Vec<usize>) -> Mint {
    let n = xs.len();

    // dp[i][j] is the number of good sub-sequences ending with i, exactly at the index j
    let mut dp: Vec<Vec<Mint>> = vec![vec![Mint::new(0); n]; 3];
    dp[xs[0]][0] = Mint::new(1);

    for j in 1..n {
        let i = xs[j];

        let (i1, i2) = other_than_k(vec![0, 1, 2], i)
            .into_iter()
            .collect_tuple()
            .unwrap();

        let mut sub = Mint::new(1);

        for k in 0..j {
            sub += dp[i1][k];
            sub += dp[i2][k];
        }

        dp[i][j] = sub;
    }

    dp.into_iter()
        .map(|row| row.into_iter().fold(Mint::new(0), |acc, x| acc + x))
        .fold(Mint::new(0), |acc, x| acc + x)
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
