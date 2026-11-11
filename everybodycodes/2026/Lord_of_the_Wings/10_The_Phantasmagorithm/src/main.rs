use itertools::Itertools;
use std::{
    collections::{HashMap, HashSet},
    io::{BufRead, stdin},
};

const GHOST_HPS: usize = 1_000_000_000_000;

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i8, i8);

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

impl Crd {
    fn from_grid(i: usize, j: usize) -> Crd {
        Crd(i as i8, j as i8)
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

fn spacial_state(ghosts: &[(Crd, Dir, usize)]) -> Vec<(Crd, Dir)> {
    ghosts.iter().map(|(crd, dir, _)| (*crd, *dir)).collect()
}

fn health_state(ghosts: &[(Crd, Dir, usize)]) -> Vec<usize> {
    ghosts.iter().map(|(_, _, hp)| *hp).collect()
}

fn play_till_repeat_return_rounds_and_hp_deltas(
    walls: &HashSet<Crd>,
    ghosts: &mut Vec<(Crd, Dir, usize)>,
) -> (usize, Vec<usize>) {
    let ss = spacial_state(ghosts);
    let hs = health_state(ghosts);

    for t in 1..=1_000_000 {
        play_one_round(walls, ghosts);

        if spacial_state(ghosts) == ss {
            let hp_deltas: Vec<usize> = health_state(ghosts)
                .into_iter()
                .enumerate()
                .map(|(i, hp)| hs[i] - hp)
                .collect();

            return (t, hp_deltas);
        }
    }

    unreachable!()
}

fn exhaust_the_weakest_return_rounds(
    walls: &HashSet<Crd>,
    ghosts: &mut Vec<(Crd, Dir, usize)>,
) -> usize {
    let n0 = ghosts.len();
    let mut rounds: usize = 0;
    let stabilization_allowance: usize = 4096;

    for t in 1..=stabilization_allowance {
        play_one_round(walls, ghosts);
        assert!(ghosts.len() <= n0);

        if ghosts.len() != n0 {
            return t;
        }
    }

    rounds += stabilization_allowance;

    let (period, hp_deltas) = play_till_repeat_return_rounds_and_hp_deltas(walls, ghosts);
    rounds += period;

    let q: usize = health_state(ghosts)
        .into_iter()
        .enumerate()
        .map(|(i, hp)| hp / hp_deltas[i])
        .min()
        .unwrap();

    for (i, ghost) in ghosts.iter_mut().enumerate() {
        ghost.2 -= hp_deltas[i] * q;
    }

    rounds += q * period;

    for t in 1..=stabilization_allowance * 2 {
        play_one_round(walls, ghosts);

        if ghosts.len() != n0 {
            return rounds + t;
        }
    }

    unreachable!()
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

    let mut rounds: usize = 0;

    while !ghosts.is_empty() {
        rounds += exhaust_the_weakest_return_rounds(&walls, &mut ghosts);
    }

    println!("{rounds}");
}
