use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn max_substring_filling_rate(xs: &[char]) -> f64 {
    let n = xs.len();
    let mut result: f64 = 0.0;

    if n > 2 {
        for i in 0..n - 2 {
            for j in i + 2..n {
                let ys = &xs[i..=j];
                let m = ys.len();

                if ys[0] == 't' && ys[m - 1] == 't' {
                    let f = ys.iter().filter(|&&y| y == 't').count();
                    let a = f as f64 - 2.0;
                    let b = m as f64 - 2.0;
                    result = result.max(a / b);
                }
            }
        }
    }

    result
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        xs: String,
    }

    let result = max_substring_filling_rate(&xs.chars().collect::<Vec<_>>());
    writeln!(writer, "{:.10}", result).unwrap();
    writer.flush().unwrap();
}
