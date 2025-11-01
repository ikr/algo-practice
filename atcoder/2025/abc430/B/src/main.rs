use proconio::input;
use proconio::marker::Bytes;
use std::{
    collections::HashSet,
    io::{BufWriter, Write, stdout},
};

fn subgid(grid: &[Vec<u8>], i0: usize, j0: usize, m: usize) -> Vec<u8> {
    let n = grid.len();
    assert!(i0 + m <= n);
    assert!(j0 + m <= n);

    let mut result = vec![];
    for row in &grid[i0..i0 + m] {
        result.extend(&row[j0..j0 + m]);
    }
    result
}

fn num_patterns(grid: Vec<Vec<u8>>, m: usize) -> usize {
    let n = grid.len();
    let gap = n - m;
    let mut ps: HashSet<String> = HashSet::new();

    for i in 0..=gap {
        for j in 0..=gap {
            ps.insert(String::from_utf8(subgid(&grid, i, j, m)).unwrap());
        }
    }

    ps.len()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        m: usize,
        xss: [Bytes; n],
    }

    let result = num_patterns(xss, m);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
