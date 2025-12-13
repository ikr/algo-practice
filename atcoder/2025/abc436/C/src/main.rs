use proconio::input;
use std::{
    collections::HashSet,
    io::{BufWriter, Write, stdout},
};

fn cells_of_2x2(top_ro: i32, left_co: i32) -> Vec<(i32, i32)> {
    vec![
        (top_ro, left_co),
        (top_ro, left_co + 1),
        (top_ro + 1, left_co),
        (top_ro + 1, left_co + 1),
    ]
}

fn possible_placements_count(rcs: Vec<(i32, i32)>) -> usize {
    let mut placed: HashSet<(i32, i32)> = HashSet::new();

    for (ro, co) in rcs {
        let cells = cells_of_2x2(ro, co);

        if cells.iter().all(|cs| !placed.contains(cs)) {
            placed.extend(cells);
        }
    }

    placed.len() / 4
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        _: i32,
        m: usize,
        rcs: [(i32, i32); m],
    }

    let result = possible_placements_count(rcs);
    writeln!(writer, "{result}").unwrap();
    writer.flush().unwrap();
}
