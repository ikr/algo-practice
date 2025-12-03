use std::io::{BufRead, stdin};

#[allow(clippy::needless_range_loop)]
fn max_joltage(xs: Vec<u64>) -> u64 {
    let n = xs.len();
    let m: usize = 12;

    // tab[i][l] is max joltage ending with the digit xs[i] and having the length l
    let mut tab: Vec<Vec<u64>> = vec![vec![0; m + 1]; n];

    for i in 0..n {
        tab[i][1] = xs[i];
    }

    for l in 1..=m {
        for i in 1..n {
            for j in 0..i {
                if tab[j][l - 1] != 0 {
                    tab[i][l] = tab[i][l].max(tab[j][l - 1] * 10 + xs[i]);
                }
            }
        }
    }

    let mut result = 0;
    for i in 0..n {
        result = result.max(tab[i][12]);
    }
    result
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();

    let grid: Vec<Vec<u64>> = lines
        .into_iter()
        .map(|s| s.bytes().map(|x| (x - b'0') as u64).collect())
        .collect();

    println!("{}", grid.into_iter().map(max_joltage).sum::<u64>());
}
