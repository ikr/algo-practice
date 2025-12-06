use std::io::{BufRead, stdin};

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

fn main() {
    let lines: Vec<String> = stdin().lock().lines().map(|line| line.unwrap()).collect();
    let n = lines.len();

    let grid: Vec<Vec<u64>> = transpose(
        lines[..n - 1]
            .iter()
            .map(|s| {
                s.split_whitespace()
                    .map(|sub| sub.parse().unwrap())
                    .collect()
            })
            .collect(),
    );

    let ops: Vec<Op> = lines[n - 1].split_whitespace().map(Op::decode).collect();
    let result: u64 = ops.into_iter().zip(grid).map(|(op, xs)| op.apply(xs)).sum();
    println!("{result}");
}
