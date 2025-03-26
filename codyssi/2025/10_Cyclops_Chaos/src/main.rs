use std::io::{self, BufRead};

fn main() {
    let grid: Vec<Vec<u16>> = io::stdin()
        .lock()
        .lines()
        .map(|line| {
            line.unwrap()
                .split_whitespace()
                .map(|s| s.parse::<u16>().unwrap())
                .collect::<Vec<_>>()
        })
        .collect();
    let n = grid.len();
    assert_eq!(grid[0].len(), n);

    let mut dp: Vec<Vec<u16>> = vec![vec![u16::MAX; n]; n];
    dp[0][0] = grid[0][0];
    for i in 1..n {
        dp[0][i] = dp[0][i - 1] + grid[0][i];
        dp[i][0] = dp[i - 1][0] + grid[i][0];
    }

    for i in 1..n {
        for j in 1..n {
            dp[i][j] = dp[i - 1][j].min(dp[i][j - 1]) + grid[i][j];
        }
    }

    let result = dp[n - 1][n - 1];
    println!("{}", result);
}
