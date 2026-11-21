use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn transpose<T>(grid: Vec<Vec<T>>) -> Vec<Vec<T>> {
    assert!(!grid.is_empty());
    let h = grid[0].len();
    let mut iters: Vec<_> = grid.into_iter().map(|n| n.into_iter()).collect();
    (0..h)
        .map(|_| {
            iters
                .iter_mut()
                .map(|n| n.next().unwrap())
                .collect::<Vec<T>>()
        })
        .collect()
}

fn solve(g: Vec<Vec<char>>) -> (String, usize) {
    let t = transpose(g.clone());

    for (grid, label) in [(g, "Faucet"), (t, "Drain")] {
        if let Some(i) = grid
            .iter()
            .enumerate()
            .find(|(_, row)| row.iter().all(|&x| x == 'x'))
            .map(|(i, _)| i)
        {
            return (label.to_string(), i + 1);
        }
    }

    unreachable!()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        _m: usize,
        ss: [String; n],
    }

    let (kind, position) = solve(ss.into_iter().map(|s| s.chars().collect()).collect());
    writeln!(writer, "{kind} {position}").unwrap();
    writer.flush().unwrap();
}
