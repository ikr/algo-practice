use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        x: i32,
        y: i32,
        z: i32,
    }

    let result = if (x - y * z) % (z - 1) == 0 && x - y * z >= 0 {
        "Yes"
    } else {
        "No"
    };
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
