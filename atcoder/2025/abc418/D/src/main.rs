use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn beautiful_substrings_count(xs: Vec<u8>) -> usize {
    let n = xs.len();
    n * (n + 1) / 2
        - xs.iter().filter(|&&x| x == 0).count()
        - xs.windows(2)
            .filter(|&xy| {
                let v = xy.to_vec();
                v == vec![0, 1] || v == vec![1, 0]
            })
            .count()
        - xs.windows(3)
            .filter(|&xy| {
                let v = xy.to_vec();
                v == vec![0, 0, 0]
                    || v == vec![1, 0, 1]
                    || v == vec![1, 1, 1]
                    || v == vec![0, 1, 1]
                    || v == vec![1, 1, 0]
            })
            .count()
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

    let result =
        beautiful_substrings_count(s.chars().map(|c| if c == '1' { 1 } else { 0 }).collect());
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
