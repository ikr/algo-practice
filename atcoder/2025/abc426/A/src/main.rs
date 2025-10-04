use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        a: String,
        b: String,
    }

    let xs = ["Ocelot", "Serval", "Lynx"];
    let i = xs.iter().position(|&x| x == a).unwrap();
    let j = xs.iter().position(|&x| x == b).unwrap();

    let result = if i >= j { "Yes" } else { "No" };
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
