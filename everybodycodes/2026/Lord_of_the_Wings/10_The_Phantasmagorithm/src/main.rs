use std::{
    collections::HashSet,
    io::{BufRead, stdin},
};

use itertools::Itertools;

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i32, i32);

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

impl Crd {
    fn from_grid(i: usize, j: usize) -> Crd {
        Crd(i as i32, j as i32)
    }
}

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
enum Dir {
    N,
    E,
    S,
    W,
}

impl Dir {
    fn delta(self) -> Crd {
        match self {
            Dir::N => Crd(-1, 0),
            Dir::E => Crd(0, 1),
            Dir::S => Crd(1, 0),
            Dir::W => Crd(0, -1),
        }
    }

    fn turn_clockwise(self) -> Dir {
        match self {
            Dir::N => Dir::E,
            Dir::E => Dir::S,
            Dir::S => Dir::W,
            Dir::W => Dir::N,
        }
    }

    fn reverse(self) -> Dir {
        match self {
            Dir::N => Dir::S,
            Dir::E => Dir::W,
            Dir::S => Dir::N,
            Dir::W => Dir::E,
        }
    }
}

fn main() {
    let grid: Vec<Vec<char>> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let height = grid.len();
    let width = grid[0].len();

    let (walls, ghosts) = (0..height).cartesian_product(0..width).fold(
        (HashSet::<Crd>::new(), HashSet::<(Crd, Dir)>::new()),
        |(mut ws, mut gs), (i, j)| {
            let crd = Crd::from_grid(i, j);

            match grid[i][j] {
                '#' => ws.insert(crd),
                '^' => gs.insert((crd, Dir::N)),
                '>' => gs.insert((crd, Dir::E)),
                'v' => gs.insert((crd, Dir::S)),
                '<' => gs.insert((crd, Dir::W)),
                '.' => false,
                _ => unreachable!(),
            };

            (ws, gs)
        },
    );

    eprintln!("{ghosts:?}");
}
