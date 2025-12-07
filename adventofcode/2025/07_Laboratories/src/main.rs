use std::io::{BufRead, stdin};

fn main() {
    let grid: Vec<Vec<char>> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let start_co = grid[0].iter().position(|&x| x == 'S').unwrap();
    let mut beam: Vec<u64> = vec![0; grid[0].len()];
    beam[start_co] = 1;

    for row in grid.into_iter().skip(1) {
        let mut new_beam: Vec<u64> = vec![0; beam.len()];

        for (co, b) in beam.iter().enumerate() {
            if row[co] == '^' {
                new_beam[co - 1] += b;
                new_beam[co + 1] += b;
            } else {
                new_beam[co] += b;
            }
        }

        beam = new_beam;
    }

    let result: u64 = beam.into_iter().sum();
    println!("{result}");
}
