use proconio::input;
use std::{
    collections::BTreeSet,
    io::{BufWriter, Write, stdout},
};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: i32,
        q: usize,
        xs: [i32; q],
    }

    let lo = -20 * n;
    let hi = 20 * n;
    // Non-overlapping intervals
    let mut ab: BTreeSet<(i32, i32)> = BTreeSet::new();

    for x in xs {
        let le = ab.range((lo, lo)..=(x - 1, hi)).last().cloned();
        let (a, b) = le.unwrap_or((lo, lo));
        assert!(a < x);

        let ri = ab.range((x, x)..=(hi, hi)).next().cloned();
        let (c, d) = ri.unwrap_or((hi, hi));
        assert!(x <= c);
        //eprintln!("x:{} ab:{:?} cd:{:?}", x, (a, b), (c, d));

        if b == x {
            ab.remove(&(a, b));
            ab.insert((a, b - 1));
        } else if c == x && d == x {
            ab.remove(&(c, d));
        } else if c == x {
            ab.remove(&(c, d));
            ab.insert((c + 1, d));
        } else if b + 1 == x && x + 1 == c {
            ab.remove(&(a, b));
            ab.remove(&(c, d));
            ab.insert((a, d));
        } else if b + 1 == x {
            ab.remove(&(a, b));
            ab.insert((a, x));
        } else if x + 1 == c {
            ab.remove(&(c, d));
            ab.insert((x, d));
        } else if a < x && x < b {
            ab.remove(&(a, b));
            ab.insert((a, x - 1));
            ab.insert((x + 1, b));
        } else {
            ab.insert((x, x));
        }

        //eprintln!("{:?}", ab);
        writeln!(writer, "{}", ab.len()).unwrap();
    }

    writer.flush().unwrap();
}
