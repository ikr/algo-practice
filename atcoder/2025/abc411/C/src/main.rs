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

    let lo = -2 * n;
    let hi = 2 * n;
    let mut ab: BTreeSet<(i32, i32)> = BTreeSet::new();

    for x in xs {
        let le = ab.range((lo, lo)..=(x - 1, hi)).last().cloned();
        let (a, b) = le.unwrap_or((lo, lo));

        let ri = ab.range((x, x)..=(hi, hi)).next().cloned();
        let (c, d) = ri.unwrap_or((hi, hi));

        if let Some((a, b)) = ivl_1 {
            eprintln!("ivl_1:{:?}", (a, b));
            if x == a && x == b {
                ab.remove(&(a, b));
            } else if x == a {
                ab.remove(&(a, b));
                ab.insert((a + 1, b));
            } else if x == b {
                ab.remove(&(a, b));
                ab.insert((a, b - 1));
            } else {
                assert!(a < x && x < b);
                ab.remove(&(a, b));
                ab.insert((a, x - 1));
                ab.insert((x + 1, b));
            }
        } else {
            let ivl_0 = ab.range((0, x - 1)..=(x - 1, n + 1)).last().cloned();
            let ivl_2 = ab.range((x + 1, x + 1)..=(x + 1, n + 1)).next().cloned();

            if let Some((a, b)) = ivl_0 {
                eprintln!("ivl_0:{:?}", (a, b));
                if let Some((c, d)) = ivl_2 {
                    eprintln!("ivl_2:{:?}", (c, d));
                    if b == x - 1 && x + 1 == c {
                        ab.remove(&(a, b));
                        ab.remove(&(c, d));
                        ab.insert((a, d));
                    } else if b == x - 1 {
                        ab.remove(&(a, b));
                        ab.insert((a, x));
                    } else if x + 1 == c {
                        ab.remove(&(c, d));
                        ab.insert((x, d));
                    } else {
                        ab.insert((x, x));
                    }
                } else {
                    if b == x - 1 {
                        ab.remove(&(a, b));
                        ab.insert((a, x));
                    } else {
                        ab.insert((x, x));
                    }
                }
            } else if let Some((c, d)) = ivl_2 {
                eprintln!("ivl_2:{:?}", (c, d));
                if x + 1 == c {
                    ab.remove(&(c, d));
                    ab.insert((x, d));
                } else {
                    ab.insert((x, x));
                }
            } else {
                ab.insert((x, x));
            }
        }

        eprintln!("{:?}", ab);
        writeln!(writer, "{}", ab.len()).unwrap();
    }

    writer.flush().unwrap();
}
