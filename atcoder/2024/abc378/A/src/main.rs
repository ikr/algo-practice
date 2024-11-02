use proconio::input;
use std::io::{self, BufWriter, Write};

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        xs: [usize; 4],
    }

    let mut freq = [0; 5];
    for x in xs {
        freq[x] += 1;
    }

    let result = freq.iter().fold(0, |acc, f| acc + f / 2);
    writeln!(writer, "{}", result).unwrap();
    writer.flush().unwrap();
}
