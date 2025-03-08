use proconio::input;
use std::io::{self, BufWriter, Write};

fn solve(xs: &[i32]) -> bool {
    xs.windows(3).any(|xs| xs[0] == xs[1] && xs[1] == xs[2])
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        xs: [i32; n],
    }

    let result = solve(&xs);
    writeln!(writer, "{}", if result { "Yes" } else { "No" }).unwrap();
    writer.flush().unwrap();
}
