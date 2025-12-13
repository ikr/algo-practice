use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        s: String,
    }

    let mut xs: Vec<char> = s.chars().collect();
    while xs.len() < n {
        xs.insert(0, 'o');
    }
    writeln!(writer, "{}", xs.into_iter().collect::<String>()).unwrap();
    writer.flush().unwrap();
}
