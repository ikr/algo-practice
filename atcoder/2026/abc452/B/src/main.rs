use proconio::input;
use std::io::{BufWriter, Write, stdout};

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        h: usize,
        w: usize,
    }

    let mut grid: Vec<Vec<char>> = vec![vec!['.'; w]; h];
    grid[0] = vec!['#'; w];
    grid[h - 1] = vec!['#'; w];

    for i in 0..h {
        grid[i][0] = '#';
        grid[i][w - 1] = '#';
    }

    for row in grid {
        let s: String = row.into_iter().collect();
        writeln!(writer, "{s}").unwrap();
    }
    writer.flush().unwrap();
}
