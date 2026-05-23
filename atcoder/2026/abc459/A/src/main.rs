use proconio::{input, marker::Usize1};
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: Usize1,
    }

    let s = "HelloWorld".to_string();

    let result = s[..n].to_string() + &s[n + 1..];
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
