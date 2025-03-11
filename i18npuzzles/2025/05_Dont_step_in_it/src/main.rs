use std::fs::read_to_string;

const POOP: char = '💩';

fn main() {
    let mut grid: Vec<Vec<char>> = read_to_string("in1")
        .unwrap()
        .lines()
        .map(|line| line.chars().collect())
        .collect();

    let w: usize = grid.iter().map(|row| row.len()).max().unwrap();
    for row in grid.iter_mut() {
        while row.len() < w {
            row.push(' ');
        }
    }

    let mut result = 0;
    let mut co: usize = 0;
    for row in grid {
        if row[co] == POOP {
            result += 1;
        }
        co += 2;
        co %= w;
    }

    println!("{}", result);
}
