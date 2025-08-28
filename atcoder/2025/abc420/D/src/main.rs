use proconio::input;
use proconio::marker::Bytes;
use std::{
    collections::VecDeque,
    io::{BufWriter, Write, stdout},
};

#[derive(Copy, Clone, Debug)]
struct State {
    level: usize,
    row: usize,
    col: usize,
}

impl State {
    fn new(level: usize, row: usize, col: usize) -> Self {
        Self { level, row, col }
    }

    fn adjacent(self, grid: &[Vec<u8>]) -> Vec<Self> {
        let h = grid.len();
        let w = grid[0].len();

        let mut result = vec![];
        let closed = if self.level == 0 {
            [b'#', b'x']
        } else {
            [b'#', b'o']
        };

        let new_level = |i: usize, j: usize, level: usize| -> usize {
            if grid[i][j] == b'?' {
                (level + 1) % 2
            } else {
                level
            }
        };

        if self.row != 0 && !closed.contains(&grid[self.row - 1][self.col]) {
            result.push(State {
                level: new_level(self.row - 1, self.col, self.level),
                row: self.row - 1,
                col: self.col,
            });
        }
        if self.row != h - 1 && !closed.contains(&grid[self.row + 1][self.col]) {
            result.push(State {
                level: new_level(self.row + 1, self.col, self.level),
                row: self.row + 1,
                col: self.col,
            });
        }
        if self.col != 0 && !closed.contains(&grid[self.row][self.col - 1]) {
            result.push(State {
                level: new_level(self.row, self.col - 1, self.level),
                row: self.row,
                col: self.col - 1,
            });
        }
        if self.col != w - 1 && !closed.contains(&grid[self.row][self.col + 1]) {
            result.push(State {
                level: new_level(self.row, self.col + 1, self.level),
                row: self.row,
                col: self.col + 1,
            });
        }
        result
    }
}

fn start_and_goal(grid: &[Vec<u8>]) -> ((usize, usize), (usize, usize)) {
    let mut s = (usize::MAX, usize::MAX);
    let mut g = (usize::MAX, usize::MAX);
    for (i, row) in grid.iter().enumerate() {
        for (j, x) in row.iter().enumerate() {
            match x {
                b'S' => s = (i, j),
                b'G' => g = (i, j),
                _ => {}
            }
        }
    }
    (s, g)
}

fn min_steps_from_start_to_goal(grid: Vec<Vec<u8>>) -> Option<usize> {
    let (s, g) = start_and_goal(&grid);
    let h = grid.len();
    let w = grid[0].len();

    let mut q: VecDeque<State> = VecDeque::from([State::new(0, s.0, s.1)]);
    let proto_level: Vec<Vec<usize>> = vec![vec![usize::MAX; w]; h];
    let mut d: Vec<Vec<Vec<usize>>> = vec![proto_level; 2];
    d[0][s.0][s.1] = 0;

    while let Some(u) = q.pop_front() {
        for v in u.adjacent(&grid) {
            if d[v.level][v.row][v.col] == usize::MAX {
                d[v.level][v.row][v.col] = d[u.level][u.row][u.col] + 1;
                q.push_back(v);
            }
        }
    }

    let answer = d[0][g.0][g.1].min(d[1][g.0][g.1]);
    if answer == usize::MAX {
        None
    } else {
        Some(answer)
    }
}

fn main() {
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    input! {
        h: usize,
        w: usize,
        grid: [Bytes; h],
    }
    assert!(grid.iter().all(|row| row.len() == w));

    if let Some(result) = min_steps_from_start_to_goal(grid) {
        writeln!(writer, "{result}").unwrap();
    } else {
        writeln!(writer, "-1").unwrap();
    }
    writer.flush().unwrap();
}
