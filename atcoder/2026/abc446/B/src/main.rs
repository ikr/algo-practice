use proconio::input;
use std::{
    collections::HashSet,
    io::{BufWriter, Write, stdout},
};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        m: usize,
    }

    let mut js: HashSet<usize> = (1..=m).collect();

    for _ in 0..n {
        input! {
            l: usize,
            xs: [usize; l],
        }

        let choice: usize = xs.into_iter().find(|x| js.contains(&x)).unwrap_or_default();
        js.remove(&choice);
        writeln!(writer, "{choice}").unwrap();
    }

    writer.flush().unwrap();
}
