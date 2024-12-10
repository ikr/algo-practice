use std::io::{self, BufRead};

fn locations_of(grid: &[Vec<u8>], x0: u8) -> Vec<(usize, usize)> {
    let mut locations = Vec::new();
    for (i, row) in grid.iter().enumerate() {
        for (j, &cell) in row.iter().enumerate() {
            if cell == x0 {
                locations.push((i, j));
            }
        }
    }
    locations
}

fn nines_reachable_from(grid: &[Vec<u8>], ro: usize, co: usize) -> usize {
    let x0 = grid[ro][co];
    if x0 == 9 {
        1
    } else {
        let mut sub = 0;
        if ro != 0 && grid[ro - 1][co] == x0 + 1 {
            sub += nines_reachable_from(grid, ro - 1, co);
        }
        if co < grid[0].len() - 1 && grid[ro][co + 1] == x0 + 1 {
            sub += nines_reachable_from(grid, ro, co + 1);
        }
        if ro < grid.len() - 1 && grid[ro + 1][co] == x0 + 1 {
            sub += nines_reachable_from(grid, ro + 1, co);
        }
        if co != 0 && grid[ro][co - 1] == x0 + 1 {
            sub += nines_reachable_from(grid, ro, co - 1);
        }
        sub
    }
}

fn main() {
    let grid: Vec<Vec<u8>> = io::stdin()
        .lock()
        .lines()
        .map(|line| {
            line.unwrap()
                .chars()
                .map(|x| x.to_digit(10).unwrap() as u8)
                .collect()
        })
        .collect();

    let zs = locations_of(&grid, 0);
    let result = zs
        .iter()
        .map(|&(ro, co)| nines_reachable_from(&grid, ro, co))
        .sum::<usize>();
    println!("{}", result);
}
