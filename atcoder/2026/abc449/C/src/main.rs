use proconio::input;
use proconio::marker::Bytes;
use std::io::{BufWriter, Write, stdout};

fn num_proper_pairs_for_x0(xs: &[u8], l: usize, r: usize, x0: u8) -> usize {
    let ss: Vec<usize> = xs
        .iter()
        .scan(0, |state, x| {
            *state += if *x == x0 { 1 } else { 0 };
            Some(*state)
        })
        .collect();

    let cumsum = |i: usize, j: usize| -> usize {
        assert!(i <= j);
        assert!(j < xs.len());
        ss[j] - if i == 0 { 0 } else { ss[i - 1] }
    };

    xs.iter()
        .enumerate()
        .map(|(i, x)| {
            if *x == x0 && i >= l {
                cumsum(i.saturating_sub(r), i - l)
            } else {
                0
            }
        })
        .sum()
}

fn num_proper_pairs(xs: Vec<u8>, l: usize, r: usize) -> usize {
    (b'a'..=b'z')
        .map(|x0| num_proper_pairs_for_x0(&xs, l, r, x0))
        .sum()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        l: usize,
        r: usize,
        mut xs: Bytes,
    }

    assert_eq!(xs.len(), n);

    let result = num_proper_pairs(xs, l, r);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
