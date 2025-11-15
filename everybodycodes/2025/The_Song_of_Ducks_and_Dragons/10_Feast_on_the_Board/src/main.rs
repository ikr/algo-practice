use std::{
    collections::VecDeque,
    io::{BufRead, stdin},
};

const RANGE: u8 = 4;

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i32, i32);

impl Crd {
    fn is_valid_in(self, grid: &[Vec<u8>]) -> bool {
        let h = grid.len();
        assert_ne!(h, 0);
        let w = grid[0].len();
        0 <= self.0 && self.0 < h as i32 && 0 <= self.1 && self.1 < w as i32
    }

    fn value_in(self, grid: &[Vec<u8>]) -> u8 {
        assert!(self.is_valid_in(grid));
        grid[self.0 as usize][self.1 as usize]
    }

    fn as_roco(self) -> (usize, usize) {
        (self.0 as usize, self.1 as usize)
    }

    fn crd_of_x_in(grid: &[Vec<u8>], x: u8) -> Self {
        for (i, row) in grid.iter().enumerate() {
            for (j, &cell) in row.iter().enumerate() {
                if cell == x {
                    return Self(i as i32, j as i32);
                }
            }
        }
        unreachable!()
    }

    fn dragon_deltas() -> Vec<Self> {
        vec![
            Crd(-2, -1),
            Crd(-2, 1),
            Crd(-1, 2),
            Crd(1, 2),
            Crd(2, 1),
            Crd(2, -1),
            Crd(-1, -2),
            Crd(1, -2),
        ]
    }
}

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

fn main() {
    let grid: Vec<Vec<u8>> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().bytes().collect())
        .collect();
    assert!(!grid.is_empty());

    let mut visited: Vec<Vec<bool>> = vec![vec![false; grid[0].len()]; grid.len()];
    let start_crd = Crd::crd_of_x_in(&grid, b'D');
    visited[start_crd.as_roco().0][start_crd.as_roco().1] = true;

    let mut q: VecDeque<(Crd, u8)> = VecDeque::from([(start_crd, 0)]);
    let mut result = 0;

    while let Some((u, u_dist)) = q.pop_front() {
        assert!(u_dist <= RANGE);

        if u.value_in(&grid) == b'S' {
            result += 1;
        }

        if u_dist != RANGE {
            let vs: Vec<Crd> = Crd::dragon_deltas()
                .into_iter()
                .filter_map(|delta| {
                    let v: Crd = u + delta;

                    if v.is_valid_in(&grid) && !visited[v.as_roco().0][v.as_roco().1] {
                        Some(v)
                    } else {
                        None
                    }
                })
                .collect();

            for v in vs {
                visited[v.as_roco().0][v.as_roco().1] = true;
                q.push_back((v, u_dist + 1));
            }
        }
    }

    println!("{result}");
}
