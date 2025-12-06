use std::io::{BufRead, stdin};

const SEP: u8 = 0xFF;

#[derive(Clone, Copy, Debug)]
enum Op {
    Add,
    Mul,
}

impl Op {
    fn decode(s: &str) -> Self {
        match s {
            "+" => Self::Add,
            "*" => Self::Mul,
            _ => unreachable!(),
        }
    }

    fn apply(self, xs: Vec<u64>) -> u64 {
        let it = xs.into_iter();
        match self {
            Self::Add => it.sum(),
            Self::Mul => it.product(),
        }
    }
}

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

fn number(ds: Vec<u8>) -> u64 {
    if ds.is_empty() {
        0
    } else {
        let mut ans: u64 = 0;
        let mut mul: u64 = 1;

        for d in ds.into_iter().rev() {
            ans += (d as u64) * mul;
            mul *= 10;
        }

        ans
    }
}

fn number_without_seps(ds: Vec<u8>) -> u64 {
    number(ds.into_iter().filter(|&d| d != SEP).collect())
}

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let input_lines_num = lines.len();

    let ops: Vec<Op> = lines[input_lines_num - 1]
        .split_whitespace()
        .map(Op::decode)
        .rev()
        .collect();

    let mut initial_grid: Vec<Vec<u8>> = lines[..input_lines_num - 1]
        .iter()
        .map(|s| {
            s.bytes()
                .map(|x| if x == b' ' { SEP } else { x - b'0' })
                .collect()
        })
        .collect();

    let initial_w: usize = initial_grid.iter().map(|row| row.len()).max().unwrap();
    for row in initial_grid.iter_mut() {
        if row.len() < initial_w {
            row.extend(vec![SEP; initial_w - row.len()]);
        }
    }

    let grid: Vec<Vec<u8>> = transpose(initial_grid).into_iter().rev().collect();
    let mut result: u64 = 0;
    let mut stash: Vec<u64> = vec![];
    let mut i: usize = 0;

    for ds in grid {
        if ds.iter().all(|&d| d == SEP) {
            result += ops[i].apply(stash);
            stash = vec![];
            i += 1;
        } else {
            stash.push(number_without_seps(ds));
        }
    }
    result += ops.last().unwrap().apply(stash);
    println!("{result}");
}
