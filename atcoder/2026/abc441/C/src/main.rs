use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn index_when_sum_reaches_y(xs: &[u64], y: u64) -> Option<usize> {
    xs.iter()
        .scan(0, |acc, x| {
            *acc += x;
            Some(*acc)
        })
        .position(|s| s >= y)
}

fn min_cups_to_drink(
    mut xs: Vec<u64>,
    sake_cups_count: usize,
    wanted_sake_mls: u64,
) -> Option<usize> {
    let n = xs.len();
    let water_cups_count = n - sake_cups_count;
    xs.sort();
    let lo_sake_mls: u64 = xs[..sake_cups_count].iter().sum();

    (lo_sake_mls >= wanted_sake_mls).then(|| {
        let i0 = index_when_sum_reaches_y(&xs[water_cups_count..], wanted_sake_mls).unwrap();
        water_cups_count + i0 + 1
    })
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        k: usize,
        x: u64,
        xs: [u64; n],
    }

    let result = if let Some(cups) = min_cups_to_drink(xs, k, x) {
        cups.to_string()
    } else {
        "-1".into()
    };

    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
