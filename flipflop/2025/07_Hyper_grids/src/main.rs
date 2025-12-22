use std::io::{BufRead, stdin};

#[allow(clippy::needless_range_loop)]
fn num_ways(h: usize, w: usize) -> u32 {
    let mut tab: Vec<Vec<u32>> = vec![vec![0; w]; h];
    for j in 0..w {
        tab[0][j] = 1;
    }
    for i in 0..h {
        tab[i][0] = 1;
    }

    for i in 1..h {
        for j in 1..w {
            tab[i][j] = tab[i - 1][j] + tab[i][j - 1];
        }
    }

    tab[h - 1][w - 1]
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let dims: Vec<(usize, usize)> = lines
        .into_iter()
        .map(|s| {
            let [w, h] = s
                .split(' ')
                .map(|sub| sub.parse().unwrap())
                .collect::<Vec<_>>()
                .try_into()
                .unwrap();
            (h, w)
        })
        .collect();

    let result: u32 = dims.into_iter().map(|(h, w)| num_ways(h, w)).sum();
    println!("{result}");
}
