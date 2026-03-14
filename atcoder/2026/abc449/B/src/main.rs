use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        mut h: u16,
        mut w: u16,
        q: u16,
    }

    for _ in 0..q {
        input! { t: u8, x: u16, }

        if t == 1 {
            let result = x * w;
            writeln!(writer, "{result}").unwrap();
            h -= x;
        } else {
            assert_eq!(t, 2);
            let result = h * x;
            writeln!(writer, "{result}").unwrap();
            w -= x;
        }
    }
    writer.flush().unwrap();
}
