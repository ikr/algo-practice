use proconio::input;
use std::{
    collections::BTreeMap,
    io::{self, BufWriter, Write},
};

fn solve(people: &[i32], sushi: &[i32]) -> Vec<Option<usize>> {
    let sushi_index_by_taste: BTreeMap<i32, usize> =
        sushi
            .iter()
            .enumerate()
            .fold(BTreeMap::new(), |mut acc, (i, &t)| {
                acc.entry(t).or_insert(i);
                acc
            });

    let mut result = vec![None; sushi.len()];
    result
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        m: usize,
        people: [i32; n],
        sushi: [i32; m],
    }

    for mbi in solve(&people, &sushi) {
        if let Some(i) = mbi {
            writeln!(writer, "{}", i).unwrap();
        } else {
            writeln!(writer, "-1").unwrap();
        }
    }
    writer.flush().unwrap();
}
