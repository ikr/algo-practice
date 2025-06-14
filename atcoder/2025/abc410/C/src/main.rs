use proconio::{input, marker::Isize1};
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: isize,
        q: usize,
    }

    let mut a: Vec<isize> = (1..=n).collect();
    let mut phase: isize = 0;

    for _ in 0..q {
        input! { opcode: u8 }
        match opcode {
            1 => {
                input! {
                    p: Isize1,
                    x: isize,
                }
                let i = ((phase + p) % n) as usize;
                a[i] = x;
            }
            2 => {
                input! { p: Isize1 }
                let i = ((phase + p) % n) as usize;
                writeln!(writer, "{}", a[i]).unwrap();
            }
            3 => {
                input! { k: isize }
                phase = (phase + k) % n;
            }
            _ => unreachable!(),
        }
    }

    writer.flush().unwrap();
}
