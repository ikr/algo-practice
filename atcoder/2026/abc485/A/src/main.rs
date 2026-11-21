use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        a: i8,
        b: i8,
    }

    let result = if a.signum() == b.signum() {
        "Yes"
    } else {
        "No"
    };
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
