use std::io::BufRead;

use itertools::Itertools;

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i32, i32);

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

fn main() {
    let lines: Vec<String> = std::io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap())
        .collect();

    eprintln!("{lines:?}");

    let start = decode_input_line_crd(&lines[0]);
    eprintln!("start: {start:?}");

    let beacons: Vec<Crd> = lines[1..lines.len() - 1]
        .iter()
        .map(|line| decode_input_line_crd(line))
        .collect();

    eprintln!("beacons: {beacons:?}");
}
