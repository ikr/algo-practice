use std::{
    collections::VecDeque,
    io::{BufRead, stdin},
};

fn main() {
    let grid: Vec<Vec<u8>> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().bytes().map(|x| x - b'0').collect())
        .collect();

    let h = grid.len();
    let w = grid[0].len();

    let mut exploded: Vec<Vec<bool>> = vec![vec![false; w]; h];
    exploded[0][0] = true;

    let mut q: VecDeque<(usize, usize)> = VecDeque::from([(0, 0)]);
    while let Some((i, j)) = q.pop_front() {
        if i != 0 && !exploded[i - 1][j] && grid[i - 1][j] <= grid[i][j] {
            exploded[i - 1][j] = true;
            q.push_back((i - 1, j));
        }
        if i != h - 1 && !exploded[i + 1][j] && grid[i + 1][j] <= grid[i][j] {
            exploded[i + 1][j] = true;
            q.push_back((i + 1, j));
        }
        if j != 0 && !exploded[i][j - 1] && grid[i][j - 1] <= grid[i][j] {
            exploded[i][j - 1] = true;
            q.push_back((i, j - 1));
        }
        if j != w - 1 && !exploded[i][j + 1] && grid[i][j + 1] <= grid[i][j] {
            exploded[i][j + 1] = true;
            q.push_back((i, j + 1));
        }
    }

    let result: usize = exploded
        .into_iter()
        .map(|row| row.into_iter().filter(|x| *x).count())
        .sum();
    eprintln!("{result}");
}
