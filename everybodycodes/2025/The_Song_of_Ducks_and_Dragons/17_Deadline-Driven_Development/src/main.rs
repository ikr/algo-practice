use itertools::Itertools;
use pathfinding::prelude::dijkstra;
use std::io::{BufRead, stdin};

const INF: i32 = 100_000_000;
const ERUPTION_STEP_DT: i32 = 30;

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i32, i32);

impl Crd {
    fn new(i: usize, j: usize) -> Self {
        Self(i as i32, j as i32)
    }

    fn get_in(self, grid: &[Vec<i32>]) -> Option<i32> {
        if self.0 >= 0 && self.1 >= 0 {
            let h = grid.len();
            let w = grid[0].len();
            let i = self.0 as usize;
            let j = self.1 as usize;

            if i < h && j < w {
                Some(grid[i][j])
            } else {
                None
            }
        } else {
            None
        }
    }

    fn dist2(self, p: Self) -> u32 {
        self.0.abs_diff(p.0).pow(2) + self.1.abs_diff(p.1).pow(2)
    }

    fn mul_by(self, k: i32) -> Self {
        Self(self.0 * k, self.1 * k)
    }
}

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

#[derive(Clone, Copy, Debug)]
enum Dir {
    N,
    E,
    S,
    W,
}

impl Dir {
    fn all() -> Vec<Self> {
        vec![Self::N, Self::E, Self::S, Self::W]
    }

    fn delta(&self) -> Crd {
        match self {
            Dir::N => Crd(-1, 0),
            Dir::E => Crd(0, 1),
            Dir::S => Crd(1, 0),
            Dir::W => Crd(0, -1),
        }
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

fn adjacent(
    grid: &[Vec<i32>],
    radius_table: &[Vec<i32>],
    eruption_radius: i32,
    u: Crd,
) -> Vec<(Crd, i32)> {
    Dir::all()
        .iter()
        .filter_map(|dir| {
            let v = u + dir.delta();

            if let Some(c) = v.get_in(grid)
                && let Some(r) = v.get_in(radius_table)
                && r > eruption_radius
            {
                Some((v, c))
            } else {
                assert_eq!(v.get_in(grid).is_none(), v.get_in(radius_table).is_none());
                None
            }
        })
        .collect()
}

fn main() {
    let grid: Vec<Vec<i32>> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().bytes().map(grid_cell_value).collect())
        .collect();

    let h = grid.len();
    let w = grid[0].len();
    let eruption_radius_bound: i32 = h.min(w) as i32;
    let [start, epicenter] = special_crds(&grid);
    let radius_table = radius_table_for(h, w, epicenter);

    let mut optimal_path_cost: i32 = INF;
    let mut optimal_eruption_radius: i32 = 0;

    for r in 0..eruption_radius_bound {
        for left_waypoint_factor in r + 1..=eruption_radius_bound {
            let left_waypoint = epicenter + Dir::W.delta().mul_by(left_waypoint_factor);

            for right_waypoint_factor in r + 1..=eruption_radius_bound {
                let right_waypoint = epicenter + Dir::E.delta().mul_by(right_waypoint_factor);

                for bottom_waypoint_factor in r + 1..=eruption_radius_bound {
                    let bottom_waypoint = epicenter + Dir::S.delta().mul_by(bottom_waypoint_factor);

                    let one = dijkstra(
                        &start,
                        |&u| adjacent(&grid, &radius_table, r, u),
                        |&u| u == left_waypoint,
                    );

                    let two = dijkstra(
                        &left_waypoint,
                        |&u| adjacent(&grid, &radius_table, r, u),
                        |&u| u == bottom_waypoint,
                    );

                    let three = dijkstra(
                        &bottom_waypoint,
                        |&u| adjacent(&grid, &radius_table, r, u),
                        |&u| u == right_waypoint,
                    );

                    let four = dijkstra(
                        &right_waypoint,
                        |&u| adjacent(&grid, &radius_table, r, u),
                        |&u| u == start,
                    );

                    match (one, two, three, four) {
                        (Some((_, a)), Some((_, b)), Some((_, c)), Some((_, d))) => {
                            let total = a + b + c + d;
                            if total <= r * ERUPTION_STEP_DT && total < optimal_path_cost {
                                optimal_path_cost = total;
                                optimal_eruption_radius = r;
                            }
                        }
                        _ => {}
                    }
                }
            }
        }
    }

    println!(
        "c:{optimal_path_cost} with r:{optimal_eruption_radius} → {}",
        optimal_path_cost * optimal_eruption_radius
    );
}
