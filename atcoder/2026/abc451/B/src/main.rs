use proconio::{input, marker::Usize1};
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        m: usize,
        aabb: [(Usize1, Usize1); n],
    }

    let mut ds: Vec<i32> = vec![0; m];
    for (a, b) in aabb {
        ds[a] -= 1;
        ds[b] += 1;
    }

    for x in ds {
        writeln!(writer, "{x}").unwrap();
    }
    writer.flush().unwrap();
}
