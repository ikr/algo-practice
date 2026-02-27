use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn log_entries_num_until_alert(k: u32, xs: Vec<u32>) -> Option<usize> {
    xs.into_iter()
        .enumerate()
        .find(|&(_, x)| x >= k)
        .map(|(i, _)| i + 1)
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        k: u32,
        xs: [u32; n],
    }

    let mb_result = log_entries_num_until_alert(k, xs);
    if let Some(result) = mb_result {
        writeln!(writer, "{result}").unwrap();
    } else {
        writeln!(writer, "-1").unwrap();
    }
    writer.flush().unwrap();
}
