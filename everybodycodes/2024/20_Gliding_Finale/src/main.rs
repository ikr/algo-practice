use std::{
    collections::HashSet,
    io::{self, BufRead},
};

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i16, i16);

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
    }
}

impl Crd {
    fn ro(&self) -> usize {
        self.0 as usize
    }

    fn co(&self) -> usize {
        self.1 as usize
    }

    fn from_indices(i: usize, j: usize) -> Crd {
        Crd(i as i16, j as i16)
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
    fn all() -> Vec<Dir> {
        vec![Dir::N, Dir::E, Dir::S, Dir::W]
    }

    fn code(&self) -> usize {
        match self {
            Dir::N => 0,
            Dir::E => 1,
            Dir::S => 2,
            Dir::W => 3,
        }
    }

    fn from_code(code: usize) -> Dir {
        match code {
            0 => Dir::N,
            1 => Dir::E,
            2 => Dir::S,
            3 => Dir::W,
            _ => panic!(),
        }
    }

    fn delta(&self) -> Crd {
        match self {
            Dir::N => Crd(-1, 0),
            Dir::E => Crd(0, 1),
            Dir::S => Crd(1, 0),
            Dir::W => Crd(0, -1),
        }
    }

    fn turn_left(&self) -> Dir {
        match self {
            Dir::N => Dir::W,
            Dir::E => Dir::N,
            Dir::S => Dir::E,
            Dir::W => Dir::S,
        }
    }

    fn turn_right(&self) -> Dir {
        match self {
            Dir::N => Dir::E,
            Dir::E => Dir::S,
            Dir::S => Dir::W,
            Dir::W => Dir::N,
        }
    }

    fn opposite(&self) -> Dir {
        match self {
            Dir::N => Dir::S,
            Dir::E => Dir::W,
            Dir::S => Dir::N,
            Dir::W => Dir::E,
        }
    }
}

#[derive(Debug)]
struct World {
    blocks: HashSet<Crd>,
    ups: HashSet<Crd>,
    downs: HashSet<Crd>,
    start: Crd,
    grid_height: usize,
    grid_width: usize,
}

impl World {
    fn from(grid: &[Vec<char>]) -> Self {
        let mut blocks = HashSet::new();
        let mut ups = HashSet::new();
        let mut downs = HashSet::new();
        let mut start = Crd(i16::MIN, i16::MIN);

        for (i, row) in grid.iter().enumerate() {
            for (j, cell) in row.iter().enumerate() {
                let p = Crd::from_indices(i, j);
                match cell {
                    '#' => {
                        blocks.insert(p);
                    }
                    '+' => {
                        ups.insert(p);
                    }
                    '-' => {
                        downs.insert(p);
                    }
                    'S' => {
                        start = p;
                    }
                    _ => {}
                };
            }
        }

        Self {
            blocks,
            ups,
            downs,
            start,
            grid_height: grid.len(),
            grid_width: grid[0].len(),
        }
    }

    fn adjacent_states(&self, s0: State) -> Vec<State> {
        s0.prospects()
            .into_iter()
            .filter(|(crd, _)| !self.blocks.contains(crd))
            .map(|(crd, dir)| {
                if self.ups.contains(&crd) {
                    s0.tick(crd, dir, 1)
                } else if self.downs.contains(&crd) {
                    s0.tick(crd, dir, -2)
                } else {
                    s0.tick(crd, dir, -1)
                }
            })
            .collect()
    }

    fn max_possible_altitude(&self) -> u16 {
        // dp(i j d) is the max possible altitude at the coordinate (i, j) when facing direction d
        // (0 - North, 1 - East, 2 - South, 3 - West), at the current moment of time.
        let mut dp: Vec<Vec<Vec<Option<u16>>>> =
            vec![vec![vec![None; 4]; self.grid_width]; self.grid_height];

        for d in Dir::all() {
            dp[self.start.ro()][self.start.co()][d.code()] = Some(1000);
        }

        for t in 1..101 {
            let mut dp_new = dp.clone();

            for (i, row) in dp.iter().enumerate() {
                for (j, cell) in row.iter().enumerate() {
                    for (d, dir_cel) in cell.iter().enumerate() {}
                }
            }

            dp = dp_new;
        }

        dp.into_iter()
            .map(|xs| {
                xs.into_iter()
                    .map(|ys| ys.into_iter().flatten().fold(0, |acc, y| acc.max(y)))
                    .max()
                    .unwrap()
            })
            .max()
            .unwrap()
    }
}

#[derive(Clone, Copy, Debug)]
struct State {
    crd: Crd,
    dir: Dir,
    alt: i16,
    t: u16,
}

impl State {
    fn new(crd: Crd) -> Self {
        Self {
            crd,
            dir: Dir::S,
            alt: 1000,
            t: 0,
        }
    }

    fn prospects(&self) -> Vec<(Crd, Dir)> {
        vec![
            (self.crd + self.dir.delta(), self.dir),
            (
                self.crd + self.dir.turn_left().delta(),
                self.dir.turn_left(),
            ),
            (
                self.crd + self.dir.turn_right().delta(),
                self.dir.turn_right(),
            ),
        ]
    }

    fn tick(&self, crd: Crd, dir: Dir, alt_delta: i16) -> Self {
        Self {
            crd,
            dir,
            alt: self.alt + alt_delta,
            t: self.t + 1,
        }
    }
}

fn main() {
    let grid: Vec<Vec<char>> = io::stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let world = World::from(&grid);
    eprintln!("{}x{} grid", world.grid_height, world.grid_width);
    println!("{}", world.max_possible_altitude());
}
