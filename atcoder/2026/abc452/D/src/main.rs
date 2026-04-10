use proconio::input;
use proconio::marker::Bytes;
use std::io::{BufWriter, Write, stdout};

fn num_substings_with_given_subeq(xs: Vec<u8>, pat: Vec<u8>) -> usize {
    let n = xs.len();
    let m = pat.len();

    // dp[i][j] is the number of sub-strings of xs ending at xs[i],
    // having pat[0..=j] as a sub-sequence.
    //
    let mut dp: Vec<Vec<usize>> = vec![vec![0; m]; n];
    if xs[0] == pat[0] {
        dp[0][0] = 1;
    }

    for i in 1..n {
        dp[i][0] = if xs[i] == pat[0] { i + 1 } else { dp[i - 1][0] };
    }

    for i in 1..n {
        for j in 1..m {
            dp[i][j] += if xs[i] == pat[j] {
                dp[i - 1][j - 1]
            } else {
                dp[i - 1][j]
            };
        }
    }

    dp.into_iter().map(|ys| ys[m - 1]).sum()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        s: Bytes,
        t: Bytes,
    }

    let n = s.len();
    let negs = num_substings_with_given_subeq(s, t);
    let result = n * (n + 1) / 2 - negs;
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
