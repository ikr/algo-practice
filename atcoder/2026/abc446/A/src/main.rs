use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        s: String,
    }

    let result: String = ("Of".to_owned() + &s.to_lowercase()).to_string();
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
