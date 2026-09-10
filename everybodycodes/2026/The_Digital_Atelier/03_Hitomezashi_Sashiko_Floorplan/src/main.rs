use std::io::{BufRead, stdin};

use itertools::Itertools;

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

#[derive(Clone, Copy, Debug)]
enum Dir {
    N,
    E,
    S,
    W,
}

impl Dir {
    fn all() -> [Dir; 4] {
        [Self::N, Self::E, Self::S, Self::W]
    }
}

struct Grid {
    row_offsets: Vec<usize>,
    column_offsets: Vec<usize>,
}

impl Grid {
    fn has_border(&self, row: usize, column: usize, dir: Dir) -> bool {
        match dir {
            Dir::N => {
                let rm = self.row_offsets.len();
                column % 2 == self.row_offsets[row % rm]
            }
            Dir::E => self.has_border(row, column + 1, Dir::W),
            Dir::S => self.has_border(row + 1, column, Dir::N),
            Dir::W => {
                let cm = self.column_offsets.len();
                row % 2 == self.column_offsets[column % cm]
            }
        }
    }
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();

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

    let g = Grid {
        row_offsets,
        column_offsets,
    };

    let result = (0..height)
        .cartesian_product(0..width)
        .filter(|&(ro, co)| Dir::all().into_iter().all(|dir| g.has_border(ro, co, dir)))
        .count();

    println!("{result}");
}
