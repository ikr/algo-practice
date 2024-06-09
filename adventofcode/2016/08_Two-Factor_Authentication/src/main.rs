use std::io::{self, BufRead};

const H: usize = 6;
const W: usize = 50;

fn transpose<T>(grid: Vec<Vec<T>>) -> Vec<Vec<T>> {
    assert!(!grid.is_empty());
    let h = grid[0].len();
    let mut iters: Vec<_> = grid.into_iter().map(|n| n.into_iter()).collect();
    (0..h)
        .map(|_| {
            iters
                .iter_mut()
                .map(|n| n.next().unwrap())
                .collect::<Vec<T>>()
        })
        .collect()
}

enum Op {
    Rect { width: usize, height: usize },
    RowRotate { row: usize, shift: usize },
    ColRotate { col: usize, shift: usize },
}

impl Op {
    fn apply(&self, mut grid: Vec<Vec<char>>) -> Vec<Vec<char>> {
        match self {
            Op::Rect { width, height } => {
                for row in grid.iter_mut().take(*height) {
                    for x in row.iter_mut().take(*width) {
                        *x = '#';
                    }
                }
            }
            Op::RowRotate { row, shift } => {
                let xs = grid.get_mut(*row).unwrap();
                xs.rotate_right(*shift);
            }
            Op::ColRotate { col, shift } => {
                grid = transpose(grid);
                let xs = grid.get_mut(*col).unwrap();
                xs.rotate_right(*shift);
                grid = transpose(grid);
            }
        }
        grid
    }
}

fn decode_rect(src: &str) -> Op {
    let parts: Vec<usize> = src
        .strip_prefix("rect ")
        .unwrap()
        .split('x')
        .map(|s| s.parse().unwrap())
        .collect();
    assert!(parts.len() == 2);
    Op::Rect {
        width: parts[0],
        height: parts[1],
    }
}

fn parts_of_rotate_source(prefix: &str, src: &str) -> Vec<usize> {
    src.strip_prefix(prefix)
        .unwrap()
        .split(" by ")
        .map(|s| s.parse().unwrap())
        .collect()
}

fn decode_row_rotate(src: &str) -> Op {
    let parts = parts_of_rotate_source("rotate row y=", src);
    assert!(parts.len() == 2);
    Op::RowRotate {
        row: parts[0],
        shift: parts[1],
    }
}

fn decode_col_rotate(src: &str) -> Op {
    let parts = parts_of_rotate_source("rotate column x=", src);
    assert!(parts.len() == 2);
    Op::ColRotate {
        col: parts[0],
        shift: parts[1],
    }
}

fn decode_op(src: &str) -> Op {
    if src.starts_with("re") {
        decode_rect(src)
    } else if src.starts_with("rotate r") {
        decode_row_rotate(src)
    } else {
        decode_col_rotate(src)
    }
}

fn print_grid(grid: &[Vec<char>]) {
    for row in grid {
        println!("{}", row.iter().collect::<String>());
    }
}

fn main() {
    let ops: Vec<Op> = io::stdin()
        .lock()
        .lines()
        .map(|line| decode_op(&line.unwrap()))
        .collect();

    let grid0 = vec![vec!['.'; W]; H];
    let grid1 = ops.into_iter().fold(grid0, |acc, op| op.apply(acc));

    let result1 = grid1.iter().fold(0, |acc, row| {
        acc + row.iter().filter(|x| **x == '#').count()
    });
    println!("{}", result1);

    print_grid(&grid1);
}
