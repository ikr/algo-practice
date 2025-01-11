use std::io::{self, BufRead};

const PLUS_RADIUS: i32 = 6;

fn max_altitudes(grid: &[Vec<char>], start_row: &[i32]) -> Vec<Vec<i32>> {
    let h = grid.len();
    let w = grid[0].len();
    assert_eq!(start_row.len(), w);

    let mut dp: Vec<Vec<i32>> = vec![vec![-1; w]; h + 1];
    dp[0] = start_row.to_vec();

    for i in 1..=h {
        for j in 0..w {
            if i != h && grid[i][j] == '#' {
                continue;
            }

            if i != h && grid[i][j] == '+' {
                for jj in (j as i32 - PLUS_RADIUS)..(j as i32 + PLUS_RADIUS) {
                    if 0 <= jj && jj < w as i32 && dp[i - 1][jj as usize] > 0 {
                        let dj = jj.abs_diff(j as i32) as i32;
                        let da = -dj + 1;

                        if dp[i - 1][jj as usize] + da >= 0 {
                            dp[i][j] = dp[i][j].max(dp[i - 1][jj as usize] + da);
                        }
                    }
                }
            } else if i != h && grid[i][j] == '-' && dp[i - 1][j] > 0 && dp[i - 1][j] - 2 >= 0 {
                dp[i][j] = dp[i - 1][j] - 2;
            } else if dp[i - 1][j] > 0 && dp[i - 1][j] - 1 >= 0 {
                dp[i][j] = dp[i - 1][j] - 1;
            }
        }
    }

    dp
}

fn main() {
    let grid: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|line| {
            let s = line.unwrap();
            s.chars().take(s.len() - 1).skip(1).collect()
        })
        .collect();
    let h = grid.len();
    let w = grid[0].len();

    let start_column: usize = grid[0].iter().position(|c| *c == 'S').unwrap();
    let initial_altitude: i32 = 384400;
    let mut start_row: Vec<i32> = vec![-1; w];
    start_row[start_column] = initial_altitude;
    let mut offset: usize = 0;
    let mut result: usize = 0;

    loop {
        let dp = max_altitudes(&grid, &start_row);

        for (i, row) in dp.iter().take(h).enumerate() {
            for cell in row.iter() {
                if *cell != -1 {
                    result = result.max(offset + i);
                }
            }
        }

        start_row = dp.last().unwrap().clone();
        if start_row.iter().all(|x| *x == -1) {
            break;
        }
        offset += h;
    }

    println!("{}", result);
}
