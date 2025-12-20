use proconio::input;
use std::io::{BufWriter, Write, stdout};

#[derive(Clone, Copy, Debug)]
struct Deer {
    w: i64,
    p: i64,
}

impl Deer {
    fn new(wp: (i64, i64)) -> Self {
        let (w, p) = wp;
        Self { w, p }
    }
}

fn max_riders(mut deers: Vec<Deer>) -> usize {
    let hi: i64 = deers.iter().map(|d| d.p).sum();
    deers.sort_by_key(|d| d.w + d.p);

    let mut cap = hi;
    for (i, d) in deers.into_iter().enumerate() {
        if cap >= d.w + d.p {
            cap -= d.w + d.p;
        } else {
            return i;
        }
    }

    unreachable!()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        t: usize,
    }

    for _ in 0..t {
        input! {
            n: usize,
            ps: [(i64, i64); n],
        }

        let result = max_riders(ps.into_iter().map(Deer::new).collect());
        writeln!(writer, "{result}").unwrap();
    }
    writer.flush().unwrap();
}
