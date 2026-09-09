use std::{
    collections::HashSet,
    io::{BufRead, stdin},
};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
enum Dir {
    N,
    E,
    S,
    W,
}

fn decode_line_int(prefix: &str, line: String) -> usize {
    line.strip_prefix(prefix).unwrap().parse().unwrap()
}

fn decode_line_flags(prefix: &str, line: String) -> Vec<usize> {
    line.strip_prefix(prefix)
        .unwrap()
        .bytes()
        .map(|b| (b - b'0') as usize)
        .collect()
}

struct Grid {
    width: usize,
    height: usize,
    row_offsets: Vec<usize>,
    column_offsets: Vec<usize>,
}

impl Grid {
    fn cell_borders(&self, row: usize, column: usize) -> HashSet<Dir> {
        assert!(row < self.height && column < self.width);
        todo!()
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    eprintln!("{:?}", lines);

    let [
        width_line,
        height_line,
        row_offsets_line,
        column_offsets_line,
    ] = lines.try_into().unwrap();

    let width = decode_line_int("width=", width_line);
    let height = decode_line_int("height=", height_line);
    let row_offsets = decode_line_flags("horizontal-offsets=", row_offsets_line);
    let column_offsets = decode_line_flags("vertical-offsets=", column_offsets_line);

    eprintln!("height:{height} width:{width}");
    eprintln!("row_offsets:{row_offsets:?} column_offsets:{column_offsets:?}");
}
