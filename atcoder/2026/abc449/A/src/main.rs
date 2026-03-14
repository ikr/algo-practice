use proconio::input;
use std::io::{BufWriter, Write, stdout};

const PI: f64 = 3.141592653589793;

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        d: f64,
    }

    let r = d / 2.0;
    let result = PI * r * r;
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
