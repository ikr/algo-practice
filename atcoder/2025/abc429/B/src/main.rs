use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn possible_to_remove_one(xs: Vec<i32>, m: i32) -> bool {
    let s = xs.iter().sum::<i32>();
    xs.into_iter().any(|x| s - x == m)
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        m: i32,
        xs: [i32; n],
    }

    let result = if possible_to_remove_one(xs, m) {
        "Yes"
    } else {
        "No"
    };
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
