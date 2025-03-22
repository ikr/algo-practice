use proconio::input;
use std::io::{self, BufWriter, Write};

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
    }

    let mut xs: String = (if n % 2 == 0 { "==" } else { "=" }).to_string();
    while xs.len() < n {
        xs.insert(0, '-');
        xs.push('-')
    }

    writeln!(writer, "{}", xs).unwrap();
    writer.flush().unwrap();
}
