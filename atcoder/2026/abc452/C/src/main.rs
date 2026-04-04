use proconio::marker::Bytes;
use proconio::{input, marker::Usize1};
use std::collections::HashSet;
use std::io::{BufWriter, Write, stdout};

fn is_possible_crossword(
    words: &[Vec<u8>],
    lengths_and_shifts: &[(usize, usize)],
    idx: &[HashSet<(usize, usize)>],
    spine_index: usize,
) -> bool {
    let n = lengths_and_shifts.len();
    let spine = &words[spine_index];

    spine.len() == n
        && spine
            .iter()
            .zip(lengths_and_shifts)
            .all(|(&c, leshi)| idx[(c - b'a') as usize].contains(leshi))
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        n: usize,
        lengths_and_shifts: [(usize, Usize1); n],
        m: usize,
        words: [Bytes; m],
    }

    let mut idx: Vec<HashSet<(usize, usize)>> = vec![HashSet::new(); 26];
    for w in &words {
        for (i, &c) in w.iter().enumerate() {
            idx[(c - b'a') as usize].insert((w.len(), i));
        }
    }

    for j in 0..m {
        let result = if is_possible_crossword(&words, &lengths_and_shifts, &idx, j) {
            "Yes"
        } else {
            "No"
        };
        writeln!(writer, "{result}").unwrap();
    }
    writer.flush().unwrap();
}
