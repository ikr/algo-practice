use std::io::{BufRead, stdin};

fn main() {
    let grid: Vec<Vec<char>> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let start_co = grid[0].iter().position(|&x| x == 'S').unwrap();
    let mut beam: Vec<bool> = vec![false; grid[0].len()];
    beam[start_co] = true;

    let mut result = 0;
    for row in grid.into_iter().skip(1) {
        let mut new_beam = vec![false; beam.len()];

        for (co, _) in beam.iter().enumerate().filter(|(_, x)| **x) {
            if row[co] == '^' {
                new_beam[co - 1] = true;
                new_beam[co + 1] = true;
                result += 1;
            } else {
                new_beam[co] = true;
            }
        }

        beam = new_beam;
    }

    println!("{result}");
}
