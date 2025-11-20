use itertools::Itertools;
use std::io::{BufRead, stdin};

fn without_element_at<T>(mut xs: Vec<T>, i: usize) -> Vec<T> {
    xs.remove(i);
    xs
}

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i8, i8);

impl Crd {
    fn new(i: usize, j: usize) -> Self {
        Self(i as i8, j as i8)
    }

    fn in_bounds(self, height: i8, width: i8) -> bool {
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
    fn from_strings(ss: &[&str]) -> Self {
        Self::from_grid(ss.iter().map(|s| s.bytes().collect()).collect())
    }

    fn from_grid(grid: Vec<Vec<u8>>) -> Self {
        let height = grid.len() as i8;
        assert_ne!(height, 0);
        let width = grid[0].len() as i8;

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

    fn escape_row(&self, col: i8) -> i8 {
        assert!(!self.hideouts.contains(&Crd(0, col)));
        (1..=self.height)
            .rfind(|i| !self.hideouts.contains(&Crd(i - 1, col)))
            .unwrap()
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
    sheep: Vec<Crd>,
    dragon: Crd,
}

impl State {
    fn adjacent(&self, field: &Field) -> Vec<Self> {
        assert!(!self.sheep.is_empty());
        match self.next_move {
            Player::Sheep => self.sheep_adjacent(field),
            Player::Dragon => self.dragon_adjacent(field),
        }
    }

    fn sheep_adjacent(&self, field: &Field) -> Vec<Self> {
        todo!()
    }

    fn dragon_adjacent(&self, field: &Field) -> Vec<Self> {
        Crd::dragon_deltas()
            .into_iter()
            .filter_map(|delta| {
                let dragon = self.dragon + delta;

                if dragon.in_bounds(field.height, field.width) {
                    let sheep: Vec<Crd> = if let Some(k) = self.sheep_index(dragon) {
                        if field.hideouts.contains(&dragon) {
                            self.sheep.clone()
                        } else {
                            without_element_at(self.sheep.clone(), k)
                        }
                    } else {
                        self.sheep.clone()
                    };

                    let next_move = if Self::can_sheep_move(field, &sheep, dragon) {
                        Player::Sheep
                    } else {
                        Player::Dragon
                    };

                    Some(Self {
                        next_move,
                        sheep,
                        dragon,
                    })
                } else {
                    None
                }
            })
            .collect()
    }

    fn sheep_index(&self, crd: Crd) -> Option<usize> {
        self.sheep.iter().position(|&sheep_crd| sheep_crd == crd)
    }

    fn can_sheep_move(field: &Field, sheep: &[Crd], dragon: Crd) -> bool {
        assert!(dragon.in_bounds(field.height, field.width));

        sheep.iter().any(|&sheep_crd| {
            let next_crd = sheep_crd + Crd(1, 0);
            field.hideouts.contains(&next_crd) || next_crd != dragon
        })
    }
}

fn main() {
    let grid: Vec<Vec<u8>> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().bytes().collect())
        .collect();
    assert!(!grid.is_empty());

    let field = Field::from_grid(grid);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_field_creation() {
        let f = Field::from_strings(&["...", ".D."]);
        assert_eq!(f.height, 2);
        assert_eq!(f.width, 3);
    }

    #[test]
    fn test_escape_row_a() {
        let f = Field::from_strings(&["...", ".D."]);
        for j in 0..3 {
            assert_eq!(f.escape_row(j), 2);
        }
    }

    #[test]
    fn test_escape_row_b() {
        let f = Field::from_strings(&["...", "#D#", "###"]);
        assert_eq!(f.escape_row(0), 1);
        assert_eq!(f.escape_row(1), 2);
        assert_eq!(f.escape_row(2), 1);
    }
}
