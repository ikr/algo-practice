use proconio::input;
use proconio::marker::Bytes;

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

fn safe_squares_num(grid: Vec<Vec<u8>>) -> usize {
    let transposed_grid = transpose(grid.clone());
    let mut pieces_by_row = [0usize; 8];
    let mut pieces_by_column = [0usize; 8];

    for i in 0..8 {
        pieces_by_row[i] = grid[i].iter().filter(|x| **x == b'#').count();
        pieces_by_column[i] = transposed_grid[i].iter().filter(|x| **x == b'#').count();
    }

    let mut result = 0;
    for ro in 0..8 {
        for co in 0..8 {
            if pieces_by_row[ro] == 0 && pieces_by_column[co] == 0 {
                result += 1;
            }
        }
    }
    result
}

fn main() {
    input! {
        xs: [Bytes; 8],
    }

    let result = safe_squares_num(xs);
    println!("{}", result);
}
