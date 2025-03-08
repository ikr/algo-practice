use proconio::input;
use std::io::{self, BufWriter, Write};

fn prefix_sums(xs: &[i64]) -> Vec<i64> {
    xs.iter()
        .scan(0, |acc, x| {
            *acc += x;
            Some(*acc)
        })
        .collect()
}

fn prefix_maxes(xs: &[i64]) -> Vec<i64> {
    xs.iter()
        .scan(0, |acc, x| {
            let y: i64 = *acc;
            *acc = y.max(*x);
            Some(*acc)
        })
        .collect()
}

fn solve(bs: &[i64], ws: &[i64]) -> i64 {
    let n = bs.len();
    let m = ws.len();

    let bss = prefix_sums(bs);
    let wss = prefix_sums(ws);
    let wsm = prefix_maxes(&wss);

    let mut result = 0;
    for i in 0..n {
        result = result.max(bss[i] + wsm[i.min(m - 1)]);
    }
    result
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        m: usize,
        mut bs: [i64; n],
        mut ws: [i64; m],
    }

    bs.sort();
    bs.reverse();
    ws.sort();
    ws.reverse();

    let result = solve(&bs, &ws);
    writeln!(writer, "{}", result).unwrap();
    writer.flush().unwrap();
}
