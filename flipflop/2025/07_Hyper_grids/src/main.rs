use std::io::{BufRead, stdin};

#[allow(clippy::needless_range_loop)]
fn num_ways(a: usize, b: usize, c: usize) -> u32 {
    let mut tab: Vec<Vec<Vec<u32>>> = vec![vec![vec![0; c]; b]; a];
    for i in 0..a {
        tab[i][0][0] = 1;
    }
    for j in 0..b {
        tab[0][j][0] = 1;
    }
    for k in 0..c {
        tab[0][0][k] = 1;
    }

    for i in 1..a {
        for j in 1..b {
            tab[i][j][0] = tab[i - 1][j][0] + tab[i][j - 1][0];
        }
    }

    todo!();

    tab[a - 1][b - 1][c - 1]
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let dims: Vec<(usize, usize, usize)> = lines
        .into_iter()
        .map(|s| {
            let [a, b] = s
                .split(' ')
                .map(|sub| sub.parse().unwrap())
                .collect::<Vec<_>>()
                .try_into()
                .unwrap();
            (a, b, a)
        })
        .collect();

    let result: u32 = dims.into_iter().map(|(a, b, c)| num_ways(a, b, c)).sum();
    println!("{result}");
}
