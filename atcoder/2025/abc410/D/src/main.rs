use proconio::{input, marker::Usize1};
use std::io::{BufWriter, Write, stdout};

fn min_walk_xor(n: usize, edges: Vec<(usize, usize, i16)>) -> i16 {
    todo!()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        m: usize,
        edges: [(Usize1, Usize1, i16); m],
    }

    let result = min_walk_xor(n, edges);
    writeln!(writer, "{}", result).unwrap();
    writer.flush().unwrap();
}
