use proconio::input;
use std::io::{self, BufWriter, Write};

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize
    }

    let mut xs: Vec<i32> = vec![0; 100];

    for _ in 0..n {
        input! {
            query_type: u8
        }

        if query_type == 1 {
            input! {
                x: i32
            }
            xs.insert(0, x);
        } else {
            assert_eq!(query_type, 2);
            writeln!(writer, "{}", xs[0]).unwrap();
            xs.remove(0);
        }
    }

    writer.flush().unwrap();
}
