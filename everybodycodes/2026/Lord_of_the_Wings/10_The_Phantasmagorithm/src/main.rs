use itertools::Itertools;
use std::{
    collections::{HashMap, HashSet},
    io::{BufRead, stdin},
};

const GHOST_HPS: usize = 10_000;

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

fn play_one_round(walls: &HashSet<Crd>, ghosts: &mut Vec<(Crd, Dir, usize)>) {
    for g in ghosts.iter_mut() {
        let (crd0, dir0, hp0) = *g;
        let crd1 = crd0 + dir0.delta();

        *g = if walls.contains(&crd1) {
            (crd0, dir0.turn_clockwise(), hp0 - 1)
        } else {
            (crd1, dir0, hp0)
        }
    }

    ghosts.retain(|(_, _, hp)| *hp != 0);

    let fqs: HashMap<Crd, usize> = ghosts
        .iter()
        .map(|&(crd, _, _)| crd)
        .counts()
        .into_iter()
        .filter(|&(_, f)| f > 1)
        .collect();

    for g in ghosts.iter_mut() {
        let (crd0, dir0, hp0) = *g;

        if fqs.contains_key(&crd0) {
            *g = (crd0, dir0.reverse(), hp0 - 1);
        }
    }

    ghosts.retain(|(_, _, hp)| *hp != 0);
}

fn main() {
    let grid: Vec<Vec<char>> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let height = grid.len();
    let width = grid[0].len();

    let (walls, mut ghosts) = (0..height).cartesian_product(0..width).fold(
        (HashSet::<Crd>::new(), Vec::<(Crd, Dir, usize)>::new()),
        |(mut ws, mut gs), (i, j)| {
            let crd = Crd::from_grid(i, j);

            match grid[i][j] {
                '#' => {
                    ws.insert(crd);
                }
                '^' => gs.push((crd, Dir::N, GHOST_HPS)),
                '>' => gs.push((crd, Dir::E, GHOST_HPS)),
                'v' => gs.push((crd, Dir::S, GHOST_HPS)),
                '<' => gs.push((crd, Dir::W, GHOST_HPS)),
                '.' => {}
                _ => unreachable!(),
            };

            (ws, gs)
        },
    );

    for t in 1..=1_000_000 {
        play_one_round(&walls, &mut ghosts);

        if ghosts.is_empty() {
            println!("{t}");
            break;
        }
    }
}
