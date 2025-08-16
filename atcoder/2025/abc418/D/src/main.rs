use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn beautiful_substrings_count(xs: Vec<u8>) -> usize {
    let n = xs.len();
    let mut beau: Vec<usize> = vec![0; n];
    let mut ugly: Vec<usize> = vec![0; n];

    if xs[0] == 1 {
        beau[0] = 1;
        ugly[0] = 0;
    } else {
        beau[0] = 0;
        ugly[0] = 1;
    }

    for i in 1..n {
        match (xs[i - 1], xs[i]) {
            (0, 0) => {
                beau[i] = ugly[i - 1];
                ugly[i] = beau[i - 1] + 1;
            }
            (0, 1) => {
                beau[i] = beau[i - 1] + 1;
                ugly[i] = ugly[i - 1];
            }
            (1, 0) => {
                beau[i] = ugly[i - 1];
                ugly[i] = beau[i - 1] + 1;
            }
            (1, 1) => {
                beau[i] = ugly[i - 1] + 1;
                ugly[i] = beau[i - 1];
            }
            _ => unreachable!(),
        }
    }

    beau.into_iter().sum()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        s: String,
    }
    assert_eq!(s.len(), n);

    let xs: Vec<u8> = s.chars().map(|c| if c == '1' { 1 } else { 0 }).collect();
    let result = beautiful_substrings_count(xs);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
