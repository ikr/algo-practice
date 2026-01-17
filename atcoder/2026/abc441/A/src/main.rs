use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        p: i32,
        q: i32,
        x: i32,
        y: i32,
    }

    let yes = p <= x && x < p + 100 && q <= y && y < q + 100;
    let result = if yes { "Yes" } else { "No" };
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
