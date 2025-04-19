use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn solve(xs: &str) -> String {
    xs.chars().filter(|c| c.is_uppercase()).collect()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        xs: String,
    }

    let result = solve(&xs);
    writeln!(writer, "{}", result).unwrap();
    writer.flush().unwrap();
}
