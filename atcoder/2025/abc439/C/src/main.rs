use itertools::Itertools;
use proconio::input;
use std::{
    collections::BTreeSet,
    io::{BufWriter, Write, stdout},
};

fn good_not_exceeding(hi: u64) -> Vec<u64> {
    let squares: Vec<u64> = (1..=hi).map(|x| x * x).collect();

    squares
        .into_iter()
        .tuple_combinations()
        .filter_map(|(x, y)| {
            let a = x * x + y * y;
            if a <= hi { Some(x) } else { None }
        })
        .collect::<BTreeSet<_>>()
        .into_iter()
        .collect()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
       hi: u64,
    }

    let result = good_not_exceeding(hi);
    writeln!(writer, "{}", result.len()).unwrap();
    writeln!(writer, "{}", result.into_iter().join(" ")).unwrap();
    writer.flush().unwrap();
}
