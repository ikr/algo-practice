use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        xs: [i32; n],
    }

    for (i, &x) in xs.iter().enumerate() {
        let mbj = xs[..i].iter().rposition(|&y| y > x);
        if let Some(j) = mbj {
            writeln!(writer, "{}", j + 1).unwrap();
        } else {
            writeln!(writer, "-1").unwrap();
        }
    }

    writer.flush().unwrap();
}
