use itertools::Itertools;
use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn p_k(xs: &[u8], k: u8) -> f64 {
    let n = xs.len();
    assert_eq!(n, 6);
    let fq = xs.iter().cloned().counts();
    let p: f64 = *fq.get(&k).unwrap_or(&0) as f64;
    p / 6.0
}

fn p_456(xss: Vec<Vec<u8>>) -> f64 {
    [4u8, 5u8, 6u8]
        .into_iter()
        .permutations(3)
        .map(|kk| {
            kk.into_iter()
                .zip(xss.iter())
                .map(|(k, xs)| p_k(xs, k))
                .product::<f64>()
        })
        .sum::<f64>()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        xss: [[u8; 6]; 3],
    }

    let result = p_456(xss);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
