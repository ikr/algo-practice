use ac_library::Dsu;
use proconio::input;
use std::{
    io::{BufWriter, Write, stdout},
    u32,
};

fn lowest_k_gap(lrs: Vec<(u32, u32)>, k: usize) -> Option<u32> {
    let n = lrs.len();
    let mut dsu = Dsu::new(n);

    let mut by_l_desc: Vec<usize> = (0..n).collect();
    by_l_desc.sort_by(|&i, &j| lrs[j].0.cmp(&lrs[i].0));

    let mut by_r_asc: Vec<usize> = (0..n).collect();
    by_r_asc.sort_by(|&i, &j| lrs[i].1.cmp(&lrs[j].1));

    let mut edges_count: usize = 0;
    let mut result: u32 = u32::MAX;

    for ri in by_r_asc {
        while let Some(li) = by_l_desc.pop() {
            if lrs[ri].1 < lrs[li].0 && !dsu.same(ri, li) {
                edges_count += 1;
                dsu.merge(ri, li);
                result = result.min(lrs[li].0 - lrs[ri].1);
                break;
            }
        }
    }

    (edges_count == k).then_some(result)
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        k: usize,
        lrs: [(u32, u32); n],
    }

    let result = match lowest_k_gap(lrs, k) {
        Some(a) => a.to_string(),
        None => "-1".to_string(),
    };
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
