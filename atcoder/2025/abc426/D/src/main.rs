use proconio::input;
use proconio::marker::Bytes;
use std::{
    io::{BufWriter, Write, stdout},
    usize,
};

fn min_ops(xs: &[u8], target: u8) -> usize {
    let elops = |x: u8| -> usize { if x == target { 2 } else { 1 } };
    let n = xs.len();

    let mut pref: Vec<usize> = vec![elops(xs[0]); n];
    for i in 1..n {
        pref[i] = pref[i - 1] + elops(xs[i]);
    }

    let mut suff: Vec<usize> = vec![elops(*xs.last().unwrap()); n];
    for i in (0..n - 1).rev() {
        suff[i] = suff[i + 1] + elops(xs[i]);
    }

    let mut result = usize::MAX;
    for i in 0..n {
        let a = if i == 0 { 0 } else { pref[i - 1] };
        let b = if i == n - 1 { 0 } else { suff[i + 1] };
        result = result.min(sub);
    }
    result
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        t: u32,
    }

    for _ in 0..t {
        input! {
            n: usize,
            mut xs: Bytes,
        }
        assert_eq!(xs.len(), n);

        for x in &mut xs {
            *x -= b'0';
        }

        let mut result = usize::MAX;
        result = result.min(min_ops(&xs, 0));
        result = result.min(min_ops(&xs, 1));

        writeln!(writer, "{result}").unwrap();
    }

    writer.flush().unwrap();
}
