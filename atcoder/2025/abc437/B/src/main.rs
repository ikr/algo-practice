use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn max_freq_among_rows(grid: Vec<Vec<i32>>, xs: Vec<i32>) -> usize {
    let fqs: Vec<usize> = grid
        .into_iter()
        .map(|row| row.into_iter().filter(|cell| xs.contains(cell)).count())
        .collect();

    fqs.into_iter().max().unwrap()
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        h: usize,
        w: usize,
        n: usize,
        grid: [[i32; w]; h],
        xs: [i32; n],
    }

    let result = max_freq_among_rows(grid, xs);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
