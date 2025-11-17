use itertools::Itertools;
use std::{
    collections::HashSet,
    io::{BufRead, stdin},
};

const ROUNDS: usize = 20;

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i8, i8);

impl Crd {
    fn new(i: usize, j: usize) -> Self {
        Self(i as i8, j as i8)
    }

    fn is_valid_in(self, height: i8, width: i8) -> bool {
        0 <= self.0 && self.0 < height && 0 <= self.1 && self.1 < width
    }

    fn crds_of_xs_in(grid: &[Vec<u8>], x: u8) -> Vec<Self> {
        let h = grid.len();
        assert_ne!(h, 0);
        let w = grid[0].len();

        (0..h)
            .cartesian_product(0..w)
            .filter_map(|(i, j)| {
                if grid[i][j] == x {
                    Some(Crd::new(i, j))
                } else {
                    None
                }
            })
            .collect()
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

struct Field {
    height: i8,
    width: i8,
    initial_sheep: Vec<Crd>,
    initial_dragon: Crd,
    hideouts: Vec<Crd>,
}

impl Field {
    fn from_rows(rows: &[&str]) -> Self {
        let height = rows.len() as i8;
        assert_ne!(height, 0);
        let width = rows[0].len() as i8;

        let grid: Vec<Vec<u8>> = rows.iter().map(|s| s.bytes().collect()).collect();
        let initial_sheep = Crd::crds_of_xs_in(&grid, b'S');
        let initial_dragon = Crd::crds_of_xs_in(&grid, b'D')[0];
        let hideouts = Crd::crds_of_xs_in(&grid, b'#');

        Self {
            height,
            width,
            initial_sheep,
            initial_dragon,
            hideouts,
        }
    }
}

#[derive(Clone, Copy)]
enum Player {
    Sheep,
    Dragon,
}

#[derive(Clone)]
struct State {
    next_move: Player,
}

fn sheep_move(hideouts: &HashSet<Crd>, dragon: &HashSet<Crd>, crds: HashSet<Crd>) -> HashSet<Crd> {
    crds.into_iter()
        .filter_map(|crd| {
            let new_crd = crd + Crd(1, 0);

            if hideouts.contains(&new_crd) || !dragon.contains(&new_crd) {
                Some(new_crd)
            } else {
                None
            }
        })
        .collect()
}

fn possible_dragon_by_time(grid: &[Vec<u8>]) -> Vec<HashSet<Crd>> {
    let start_crd: Crd = Crd::crds_of_xs_in(grid, b'D')[0];

    (0..=ROUNDS)
        .scan(HashSet::new(), |state, _| {
            if state.is_empty() {
                *state = HashSet::from([start_crd]);
                Some(state.clone())
            } else {
                let mut result: HashSet<Crd> = HashSet::new();

                for &crd in state.iter() {
                    for delta in Crd::dragon_deltas() {
                        let new_crd: Crd = crd + delta;

                        if new_crd.is_valid_in(grid.len() as i8, grid[0].len() as i8) {
                            result.insert(new_crd);
                        }
                    }
                }

                *state = result;
                Some(state.clone())
            }
        })
        .collect()
}

fn main() {
    let grid: Vec<Vec<u8>> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().bytes().collect())
        .collect();
    assert!(!grid.is_empty());

    let mut sheep: HashSet<Crd> = Crd::crds_of_xs_in(&grid, b'S').into_iter().collect();
    let hideouts: HashSet<Crd> = Crd::crds_of_xs_in(&grid, b'#').into_iter().collect();

    let mut result = 0;
    for dbt in possible_dragon_by_time(&grid).into_iter().skip(1) {
        for d_crd in &dbt {
            if !hideouts.contains(d_crd) && sheep.contains(d_crd) {
                result += 1;
                sheep.remove(d_crd);
            }
        }

        let pre_count = sheep.len();
        sheep = sheep_move(&hideouts, &dbt, sheep);
        let post_count = sheep.len();
        result += pre_count - post_count;
    }
    println!("{result}");
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_field_creation() {
        let f = Field::from_rows(&["...", ".D."]);
        assert_eq!(f.height, 2);
        assert_eq!(f.width, 3);
    }
}
