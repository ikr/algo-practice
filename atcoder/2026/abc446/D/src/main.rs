use proconio::input;
use std::{
    collections::HashMap,
    io::{BufWriter, Write, stdout},
};

fn max_proper_subseq_length(xs: Vec<u32>) -> usize {
    let mut ls: HashMap<u32, usize> = HashMap::new();

    for x in xs {
        let prefix_length = *ls.get(&(x - 1)).unwrap_or(&0);
        let cur: usize = *ls.get(&x).unwrap_or(&0);
        ls.insert(x, cur.max(prefix_length + 1));
    }

    ls.into_values().max().unwrap()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        xs: [u32; n],
    }

    let result = max_proper_subseq_length(xs);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
