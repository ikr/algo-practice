use std::{
    collections::HashSet,
    io::{BufRead, stdin},
    iter::successors,
};

type Grid = Vec<Vec<i8>>;
type Ray = Vec<(usize, usize)>;
type Alley = Vec<i8>;

const EMPTY: i8 = i8::MIN;
const TARGET_YIELD: usize = 100_000;

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

fn diag_alley_ps(grid: &[Vec<i8>], head: (usize, usize)) -> Ray {
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

fn all_diag_alley_ps(grid: &[Vec<i8>]) -> Vec<Ray> {
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

fn all_horz_alley_ps(grid: &[Vec<i8>]) -> Vec<Ray> {
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

fn lit_indices(xs: Alley) -> Vec<usize> {
    xs.into_iter()
        .enumerate()
        .fold((vec![], 0i8), |(mut r, hi), (i, x)| {
            if x > hi {
                r.push(i);
            }

            (r, ((hi - 1).max(0).max(x - 1)))
        })
        .0
}

fn all_ray_sets(grid: Grid) -> Vec<Vec<Ray>> {
    let south_east = all_diag_alley_ps(&grid);
    let north_west = reverse_rows(south_east.clone());

    let idx = reverse_rows(meta_grid(&grid));

    let south_west: Vec<Ray> = south_east
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

fn lit_locs(grid: &[Vec<i8>], rays: &[Ray]) -> HashSet<(usize, usize)> {
    rays.iter()
        .flat_map(|ray| {
            let alley: Alley = ray.iter().map(|&(i, j)| grid[i][j]).collect();
            let idx = lit_indices(alley);
            idx.into_iter().map(|k| ray[k])
        })
        .collect()
}

fn tick_return_yield(mut grid: Grid, lit: HashSet<(usize, usize)>) -> (Grid, usize) {
    let mut yld = 0;

    for (i, row) in grid.iter_mut().enumerate() {
        for (j, x) in row.iter_mut().enumerate() {
            if *x != EMPTY && (*x <= 0 || lit.contains(&(i, j))) {
                *x += 1;
            }

            if *x == 10 {
                *x = -2;
                yld += 1;
            }
        }
    }

    (grid, yld)
}

fn main() {
    let mut grid: Grid = stdin()
        .lock()
        .lines()
        .map(|line| {
            line.unwrap()
                .bytes()
                .map(|x| if x == b'.' { EMPTY } else { (x - b'0') as i8 })
                .collect()
        })
        .collect();

    let ray_sets = all_ray_sets(grid.clone());
    let mut yld: usize = 0;
    let mut nrg: usize = 0;

    for t in 0..100_000_000 {
        let lit = lit_locs(&grid, &ray_sets[t % ray_sets.len()]);
        nrg += lit.len();

        let (new_grid, delta) = tick_return_yield(grid, lit);
        yld += delta;
        grid = new_grid;

        if yld >= TARGET_YIELD {
            break;
        }
    }

    println!("{nrg}");
}
