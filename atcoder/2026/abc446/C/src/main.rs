use proconio::input;
use std::{
    collections::VecDeque,
    io::{BufWriter, Write, stdout},
};

fn final_eggs_count(d: usize, aa: Vec<u32>, bb: Vec<u32>) -> u32 {
    let mut q: VecDeque<(usize, u32)> = VecDeque::new();

    for (day, (a, b)) in aa.into_iter().zip(bb).enumerate() {
        q.push_back((day, a));
        let mut to_use = b;

        while to_use != 0 {
            let (dx, x) = q.pop_front().unwrap();
            assert_ne!(x, 0);
            let cur = to_use.min(x);

            if x > cur {
                q.push_front((dx, x - cur));
            }

            to_use -= cur;
        }

        while let Some(&(dx, _)) = q.front()
            && day - dx >= d
        {
            q.pop_front();
        }
    }

    q.into_iter().map(|(_, x)| x).sum()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! { tc: usize }

    for _ in 0..tc {
        input! {
            n: usize,
            d: usize,
            aa: [u32; n],
            bb: [u32; n],
        }

        let result = final_eggs_count(d, aa, bb);
        writeln!(writer, "{result}").unwrap();
    }

    writer.flush().unwrap();
}
