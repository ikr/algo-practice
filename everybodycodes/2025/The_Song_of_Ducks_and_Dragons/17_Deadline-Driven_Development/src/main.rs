use itertools::Itertools;
use std::io::{BufRead, stdin};

const INF: i32 = 100_000_000;

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i32, i32);

impl Crd {
    fn new(i: usize, j: usize) -> Self {
        Self(i as i32, j as i32)
    }

    fn get_in(self, grid: &[Vec<i32>]) -> i32 {
        grid[self.0 as usize][self.1 as usize]
    }

    fn dist2(self, p: Self) -> u32 {
        self.0.abs_diff(p.0).pow(2) + self.1.abs_diff(p.1).pow(2)
    }
}

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

fn special_crds(grid: &[Vec<i32>]) -> [Crd; 2] {
    let h = grid.len();
    let w = grid[0].len();

    (0..h)
        .cartesian_product(0..w)
        .filter_map(|(i, j)| {
            if 0 < grid[i][j] && grid[i][j] < 10 {
                None
            } else {
                Some(Crd::new(i, j))
            }
        })
        .collect::<Vec<_>>()
        .try_into()
        .unwrap()
}

fn grid_cell_value(x: u8) -> i32 {
    match x {
        b'@' => INF,
        b'S' => 0,
        b'1'..b'9' => (x - b'0') as i32,
        _ => unreachable!(),
    }
}

fn radius_table_for(h: usize, w: usize, epicenter: Crd) -> Vec<Vec<i32>> {
    let mut result: Vec<Vec<i32>> = vec![vec![0; w]; h];

    for (i, row) in result.iter_mut().enumerate() {
        for (j, cell) in row.iter_mut().enumerate() {
            let r2 = epicenter.dist2(Crd::new(i, j));

            *cell = (if r2.isqrt().pow(2) == r2 {
                r2.isqrt()
            } else {
                r2.isqrt() + 1
            }) as i32
        }
    }

    result
}

fn main() {
    let grid: Vec<Vec<i32>> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().bytes().map(grid_cell_value).collect())
        .collect();

    let h = grid.len();
    let w = grid[0].len();
    let [start, epicenter] = special_crds(&grid);
    eprintln!("{h} x {w}, start: {:?}, epicenter: {:?}", start, epicenter);

    eprintln!("{:?}", radius_table_for(h, w, epicenter));
}
