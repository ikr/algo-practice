use proconio::input;
use std::{
    cmp::Reverse,
    collections::BinaryHeap,
    io::{BufWriter, Write, stdout},
};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        qs: [(u8, u32); n],
    }

    let mut xs: BinaryHeap<Reverse<u32>> = BinaryHeap::new();
    for (qtype, h0) in qs {
        if qtype == 1 {
            xs.push(Reverse(h0));
        } else {
            while let Some(Reverse(h)) = xs.peek()
                && *h <= h0
            {
                xs.pop();
            }

            assert_eq!(qtype, 2);
        }

        writeln!(writer, "{}", xs.len()).unwrap();
    }

    writer.flush().unwrap();
}
