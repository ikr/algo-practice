use proconio::input;
use proconio::marker::Bytes;
use std::io::{BufWriter, Write, stdout};

fn is_reservable(xss: Vec<Vec<u8>>, wish: u8) -> bool {
    let i: usize = (wish - b'A') as usize;
    xss.into_iter().any(|xs| xs[i] == b'o')
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        wish: char,
        xss: [Bytes; n],
    }

    let result = if is_reservable(xss, wish as u8) {
        "Yes"
    } else {
        "No"
    };
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
