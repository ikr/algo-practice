use itertools::Itertools;
use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn good_not_exceeding(hi: u64) -> Vec<u64> {
    (1..=hi)
        .take_while(|x| x * x <= hi)
        .tuple_combinations()
        .filter_map(|(a, b)| {
            let y = a * a + b * b;
            if y <= hi { Some(y) } else { None }
        })
        .counts()
        .into_iter()
        .filter_map(|(x, f)| (f == 1).then_some(x))
        .sorted()
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
