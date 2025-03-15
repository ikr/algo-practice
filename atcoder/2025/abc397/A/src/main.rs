use proconio::input;
use std::io::{self, BufWriter, Write};

fn solve(t: u16) -> u8 {
    if t >= 380 {
        1
    } else if t >= 375 {
        2
    } else {
        3
    }
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        s: String
    }

    let parts: Vec<_> = s.split('.').collect();
    let t: u16 = (parts[0].to_string() + parts[1]).parse().unwrap();

    let result = solve(t);
    writeln!(writer, "{}", result).unwrap();
    writer.flush().unwrap();
}
