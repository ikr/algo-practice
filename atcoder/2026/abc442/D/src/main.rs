use ac_library::fenwicktree::FenwickTree;
use proconio::{input, marker::Usize1};
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        q: usize,
        xs: [i32; n],
    }

    let mut ft: FenwickTree<i32> = FenwickTree::new(n, 0);
    for (i, x) in xs.into_iter().enumerate() {
        ft.add(i, x);
    }

    for _ in 0..q {
        input! { op: u8 }

        match op {
            1 => {
                input! { i: Usize1 }
                let j = i + 1;
                let a = ft.sum(i..=i);
                let b = ft.sum(j..=j);

                ft.add(i, -a + b);
                ft.add(j, -b + a);
            }
            2 => {
                input! {
                    i: Usize1,
                    j: Usize1,
                }

                let result = ft.sum(i..=j);
                writeln!(writer, "{result}").unwrap();
            }
            _ => unreachable!(),
        }
    }

    writer.flush().unwrap();
}
