use ac_library::Dsu;
use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn indices_sorted_by_pair_components(lrs: &[(u32, u32)]) -> (Vec<usize>, Vec<usize>) {
    let mut by_l: Vec<usize> = (0..lrs.len()).collect();
    by_l.sort_by(|&i, &j| lrs[i].0.cmp(&lrs[j].0));

    let mut by_r: Vec<usize> = (0..lrs.len()).collect();
    by_r.sort_by(|&i, &j| lrs[i].1.cmp(&lrs[j].1));

    (by_l, by_r)
}

fn farthest_apart_edges(lrs: &[(u32, u32)], by_l: &[usize], by_r: &[usize]) -> Vec<(usize, usize)> {
    lrs.iter()
        .enumerate()
        .fold(vec![], |mut acc, (u, &(l, r))| {
            todo!();
            acc
        })
}

fn lowest_k_gap(lrs: Vec<(u32, u32)>, k: usize) -> u32 {
    let (by_l, by_r) = indices_sorted_by_pair_components(&lrs);
    todo!()
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

    let result = lowest_k_gap(lrs, k);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
