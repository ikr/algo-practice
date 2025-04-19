use proconio::input;
use std::{
    collections::VecDeque,
    io::{BufWriter, Write, stdout},
};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! { q: usize }

    let mut xs: VecDeque<u8> = VecDeque::new();

    for _ in 0..q {
        input! { qt: u8 }

        if qt == 1 {
            input! { x: u8 }
            xs.push_back(x);
        } else {
            assert_eq!(qt, 2);
            if let Some(x) = xs.pop_front() {
                writeln!(writer, "{}", x).unwrap();
            } else {
                panic!("Empty queue");
            }
        }
    }

    writer.flush().unwrap();
}
