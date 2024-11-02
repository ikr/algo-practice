use proconio::input;
use std::{
    collections::HashMap,
    io::{self, BufWriter, Write},
};

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        xs: [i32; n],
    }

    let mut ys = vec![0; n];
    let mut latest_index_by_value: HashMap<i32, usize> = HashMap::new();

    for (i, x) in xs.into_iter().enumerate() {
        if let Some(ix) = latest_index_by_value.get(&x) {
            ys[i] = (*ix as i32) + 1;
        } else {
            ys[i] = -1;
        }

        latest_index_by_value.insert(x, i);
    }

    writeln!(
        writer,
        "{}",
        ys.into_iter()
            .map(|y| y.to_string())
            .collect::<Vec<_>>()
            .join(" ")
    )
    .unwrap();
    writer.flush().unwrap();
}
