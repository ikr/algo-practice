use std::{collections::HashSet, io::BufRead};

use itertools::Itertools;

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i32, i32);

impl Crd {
    fn halfway_to(self, dst: Crd) -> Crd {
        Crd((self.0 + dst.0) / 2, (self.1 + dst.1) / 2)
    }
}

fn decode_input_line_crd(line: &str) -> Crd {
    let i = line.find('[').unwrap();
    let j = line.find(']').unwrap();

    let (x, y) = line[i + 1..j]
        .split(',')
        .map(|s| s.parse().unwrap())
        .collect_tuple()
        .unwrap();

    Crd(x, y)
}

fn decode_input_line_moves(line: &str) -> Vec<usize> {
    line.strip_prefix("MOVES=")
        .unwrap()
        .bytes()
        .map(|b| (b - b'A') as usize)
        .collect()
}

fn main() {
    let lines: Vec<String> = std::io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap())
        .collect();

    let start = decode_input_line_crd(&lines[0]);

    let beacons: Vec<Crd> = lines[1..lines.len() - 1]
        .iter()
        .map(|line| decode_input_line_crd(line))
        .collect();

    let moves = decode_input_line_moves(lines.last().unwrap());

    let (illuminated, _) =
        moves
            .into_iter()
            .fold((HashSet::from([start]), start), |(mut ps, p), i| {
                let q = p.halfway_to(beacons[i]);
                ps.insert(q);
                (ps, q)
            });

    println!("{}", illuminated.len());
}
