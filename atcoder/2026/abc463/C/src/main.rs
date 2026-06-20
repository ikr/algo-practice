use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        mut hls: [(u32, u32); n],
        q: usize,
        ts: [u32; q],
    }

    hls.sort_by_key(|(_, l)| *l);
    let mut suff_hi: Vec<u32> = vec![hls[n - 1].0; n];

    for i in (0..n - 1).rev() {
        suff_hi[i] = suff_hi[i + 1].max(hls[i].0);
    }

    for t in ts {
        let i = hls.partition_point(|(_, l)| *l <= t);
        let result: u32 = suff_hi[i];
        writeln!(writer, "{result}").unwrap();
    }

    writer.flush().unwrap();
}
