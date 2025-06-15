use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn max_defeated_monsters(h0: usize, m0: usize, ab: Vec<(usize, usize)>) -> usize {
    let n = ab.len();

    // dp[i][j] — Some(k) if max mana after defeating monster i with health j remaining is k,
    // or None, if such a state is impossible
    let mut dp: Vec<Vec<Option<usize>>> = vec![vec![None; h0 + 1]; n + 1];
    dp[0][h0] = Some(m0);

    for i in 0..n {
        for j in 0..=h0 {
            if let Some(k) = dp[i][j] {
                let (a, b) = ab[i];

                if j >= a {
                    if let Some(cur) = dp[i + 1][j - a] {
                        dp[i + 1][j - a] = Some(cur.max(k));
                    } else {
                        dp[i + 1][j - a] = Some(k);
                    }
                }

                if k >= b {
                    if let Some(cur) = dp[i + 1][j] {
                        dp[i + 1][j] = Some(cur.max(k - b));
                    } else {
                        dp[i + 1][j] = Some(k - b);
                    }
                }
            }
        }
    }

    dp.into_iter()
        .filter(|row| row.iter().any(|x| x.is_some()))
        .count()
        - 1
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        h0: usize,
        m0: usize,
        ab: [(usize, usize); n],
    }

    let result = max_defeated_monsters(h0, m0, ab);
    writeln!(writer, "{}", result).unwrap();
    writer.flush().unwrap();
}
