use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn prefix_sums(xs: &[usize]) -> Vec<usize> {
    xs.iter()
        .scan(0usize, |s, x| {
            *s += x;
            Some(*s)
        })
        .collect()
}

fn min_xs(fs: Vec<usize>, bs: Vec<usize>) -> Vec<usize> {
    let n = fs.len();
    let ss = prefix_sums(&fs);

    bs.into_iter()
        .map(|b| {
            if b > *fs.last().unwrap() {
                usize::MAX
            } else {
                let i0 = fs.partition_point(|&f| f < b);
                assert_ne!(i0, n);

                let tail_len = n - i0;
                let pre: usize = if i0 == 0 { 0 } else { ss[i0 - 1] };
                pre + tail_len * (b - 1) + 1
            }
        })
        .collect()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        q: usize,
        mut fs: [usize; n],
        bs: [usize; q],
    }

    fs.sort();
    let results = min_xs(fs, bs);

    for r in results {
        if r == usize::MAX {
            writeln!(writer, "-1").unwrap();
        } else {
            writeln!(writer, "{r}").unwrap();
        }
    }
    writer.flush().unwrap();
}
