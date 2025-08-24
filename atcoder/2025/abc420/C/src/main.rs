use proconio::{input, marker::Usize1};
use std::io::{BufWriter, Write, stdout};

fn delta_of_update(old_pair: (i64, i64), new_pair: (i64, i64)) -> i64 {
    let (x, y) = old_pair;
    let (xx, yy) = new_pair;
    xx.min(yy) - x.min(y)
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        q: usize,
        mut aa: [i64; n],
        mut bb: [i64; n],
    }

    let mut answer: i64 = aa.iter().zip(bb.iter()).map(|(a, b)| a.min(b)).sum();

    for _ in 0..q {
        input! {
            c: char,
            i: Usize1,
            x: i64,
        }

        let old_pair = (aa[i], bb[i]);
        if c == 'A' {
            aa[i] = x;
        } else {
            assert_eq!(c, 'B');
            bb[i] = x;
        }
        let new_pair = (aa[i], bb[i]);
        answer += delta_of_update(old_pair, new_pair);
        writeln!(writer, "{answer}").unwrap();
    }

    writer.flush().unwrap();
}
