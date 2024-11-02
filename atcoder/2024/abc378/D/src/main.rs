use proconio::input;
use proconio::marker::Bytes;
use std::io::{self, BufWriter, Write};

fn num_paths_with_k_moves(k: u8, grid: &[Vec<u8>]) -> u32 {
    eprintln!("{:?}", grid);
    todo!()
}

fn main() {
    let stdout = io::stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        h: usize,
        w: usize,
        k: u8,
        grid: [Bytes; h],
    }

    assert_eq!(grid[0].len(), w);

    let result = num_paths_with_k_moves(k, &grid);
    writeln!(writer, "{}", result).unwrap();
    writer.flush().unwrap();
}
