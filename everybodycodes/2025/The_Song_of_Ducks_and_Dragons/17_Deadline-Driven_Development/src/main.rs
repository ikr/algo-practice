use itertools::Itertools;
use std::io::{BufRead, stdin};

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

fn crds_of_zeros(grid: &[Vec<i32>]) -> [Crd; 2] {
    let h = grid.len();
    let w = grid[0].len();

    (0..h)
        .cartesian_product(0..w)
        .filter_map(|(i, j)| {
            if grid[i][j] == 0 {
                Some(Crd::new(i, j))
            } else {
                None
            }
        })
        .collect::<Vec<_>>()
        .try_into()
        .unwrap()
}

fn grid_cell_value(x: u8) -> i32 {
    if x == b'@' || x == b'S' {
        0
    } else {
        (x - b'0') as i32
    }
}

fn radius_table_for(h: usize, w: usize, epicenter_crd: Crd) -> Vec<Vec<i32>> {
    let mut result: Vec<Vec<i32>> = vec![vec![0; w]; h];

    for (i, row) in result.iter_mut().enumerate() {
        for (j, cell) in row.iter_mut().enumerate() {
            let r2 = epicenter_crd.dist2(Crd::new(i, j));

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

    eprintln!("{:?}", grid);

    let h = grid.len();
    let w = grid[0].len();
    eprintln!("{h} x {w}");
    let [_, epicenter_crd] = crds_of_zeros(&grid);

    eprintln!("{:?}", radius_table_for(h, w, epicenter_crd));
}
