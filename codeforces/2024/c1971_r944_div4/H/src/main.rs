use std::collections::VecDeque;
use std::io::Write;

fn alice_can_win(grid: &[Vec<i16>]) -> bool {
    false
}

fn main() {
    let mut istream: VecDeque<i16> = std::io::read_to_string(std::io::stdin())
        .unwrap()
        .split_whitespace()
        .map(|x| x.parse::<i16>().unwrap())
        .collect();

    let mut out = std::io::stdout().lock();

    for _ in 0..istream.pop_front().unwrap() {
        let n = istream.pop_front().unwrap() as usize;
        let mut grid: Vec<Vec<i16>> = vec![vec![0; n]; 3];
        for row in grid.iter_mut() {
            for x in row.iter_mut() {
                *x = istream.pop_front().unwrap();
            }
        }

        eprintln!("{:?}", grid);

        let result = if alice_can_win(&grid) { "YES" } else { "NO" };
        writeln!(out, "{}", result).unwrap();
    }
}
