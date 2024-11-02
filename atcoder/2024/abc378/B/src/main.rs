use proconio::input;
use std::io::{self, BufWriter, Write};

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        qr: [(u32, u32); n],
        q: usize,
        td:[(usize, u32); q]
    }

    for query in td {
        let t = query.0 - 1;
        let d = query.1;

        let (q, r0) = qr[t];
        let r1 = d % q;
        let wait_days = if r1 <= r0 { r0 - r1 } else { (q - r1) + r0 };
        let result = d + wait_days;
        writeln!(writer, "{}", result).unwrap();
    }

    writer.flush().unwrap();
}
