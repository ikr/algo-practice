use proconio::{input, marker::Usize1};
use std::io::{BufWriter, Write, stdout};

fn seqs_num(xs: Vec<usize>) -> usize {
    let mut fqs: Vec<usize> = vec![0; xs.len()];
    fqs[xs[0]] = 1;

    // dp[i] is the answer when xs[i] is moved left
    let mut dp: Vec<usize> = vec![0; xs.len()];
    dp[0] = 1;

    for i in 1..xs.len() {
        dp[i] = i - 1;

        if xs[i] == xs[i - 1] {
            dp[i] -= fqs[xs[i]];
        }

        fqs[xs[i]] += 1;
    }

    dp.into_iter().sum()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        xs: [Usize1; n],
    }

    let result = seqs_num(xs);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
