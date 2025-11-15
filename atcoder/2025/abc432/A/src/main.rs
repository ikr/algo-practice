use itertools::Itertools;
use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        mut xs: [i32; 3],
    }

    xs.sort();
    xs.reverse();

    let result = xs.into_iter().join("");
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
