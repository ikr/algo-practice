use std::{
    io::{BufRead, stdin},
    iter::successors,
};

type AlleyPs = Vec<(usize, usize)>;
type AlleyPsSet = Vec<AlleyPs>;

const EMPTY: i8 = i8::MIN;

fn reverse_rows<T>(mut grid: Vec<Vec<T>>) -> Vec<Vec<T>> {
    for row in &mut grid {
        row.reverse();
    }
    grid
}

fn meta_grid<T>(grid: &[Vec<T>]) -> Vec<Vec<(usize, usize)>> {
    grid.iter()
        .enumerate()
        .map(|(i, row)| {
            row.iter()
                .enumerate()
                .map(|(j, _)| (i, j))
                .collect::<Vec<_>>()
        })
        .collect()
}

fn diag_alley_ps(grid: &[Vec<i8>], head: (usize, usize)) -> AlleyPs {
    let height = grid.len();
    let width = grid[0].len();

    successors(Some(head), |(i, j)| {
        (i + 1 < height && j + 1 < width).then_some((i + 1, j + 1))
    })
    .filter_map(|(i, j)| {
        let x = grid[i][j];
        (x != EMPTY).then_some((i, j))
    })
    .collect()
}

fn all_diag_alley_ps(grid: &[Vec<i8>]) -> AlleyPsSet {
    let left_top_column: usize = grid[0].iter().position(|&x| x != EMPTY).unwrap();
    let left_row = left_top_column;
    let right_top_column: usize = grid[0].iter().rposition(|&x| x != EMPTY).unwrap();

    let heads: Vec<(usize, usize)> = (left_top_column..=right_top_column)
        .step_by(2)
        .map(|j| (0, j))
        .chain((1..=left_row).map(|i| (i, left_top_column - i)))
        .collect();

    heads.into_iter().map(|h| diag_alley_ps(grid, h)).collect()
}

fn all_horz_alley_ps(grid: &[Vec<i8>]) -> AlleyPsSet {
    grid.iter()
        .enumerate()
        .map(|(i, row)| {
            row.iter()
                .copied()
                .enumerate()
                .filter_map(|(j, x)| (x != EMPTY).then_some((i, j)))
                .collect::<Vec<_>>()
        })
        .collect()
}

fn lit_count(xs: Vec<i8>) -> usize {
    xs.into_iter()
        .fold((0, 0i8), |(r, hi), x| {
            (if x > hi { r + 1 } else { r }, ((hi - 1).max(0).max(x - 1)))
        })
        .0
}

fn all_alley_point_sets(grid: Vec<Vec<i8>>) -> Vec<AlleyPsSet> {
    let south_east = all_diag_alley_ps(&grid);
    let north_west = reverse_rows(south_east.clone());

    let idx = reverse_rows(meta_grid(&grid));
    let south_west: AlleyPsSet = south_east
        .iter()
        .cloned()
        .map(|ps| ps.into_iter().map(|(i, j)| idx[i][j]).collect())
        .collect();

    let north_east = north_west
        .iter()
        .cloned()
        .map(|ps| ps.into_iter().map(|(i, j)| idx[i][j]).collect())
        .collect();

    let east = all_horz_alley_ps(&grid);
    let west = reverse_rows(east.clone());

    vec![south_east, south_west, west, north_west, north_east, east]
}

fn main() {
    let grid: Vec<Vec<i8>> = stdin()
        .lock()
        .lines()
        .map(|line| {
            line.unwrap()
                .bytes()
                .map(|x| if x == b'.' { EMPTY } else { (x - b'0') as i8 })
                .collect()
        })
        .collect();

    let a_alp_sets = all_alley_point_sets(grid.clone());

    let a_al_sets: Vec<Vec<Vec<i8>>> = a_alp_sets
        .into_iter()
        .map(|xss| {
            xss.into_iter()
                .map(|xs| xs.into_iter().map(|(i, j)| grid[i][j]).collect::<Vec<_>>())
                .collect::<Vec<_>>()
        })
        .collect::<Vec<_>>();

    let a_lit_counts: Vec<usize> = a_al_sets
        .into_iter()
        .map(|xss| xss.into_iter().map(lit_count).sum::<usize>())
        .collect();

    eprintln!("{a_lit_counts:?}");
    println!("{}", a_lit_counts.into_iter().sum::<usize>());
}
