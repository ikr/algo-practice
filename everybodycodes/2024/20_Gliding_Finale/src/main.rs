use std::{
    collections::{HashSet, VecDeque},
    i16,
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

#[derive(Clone, Copy, Debug)]
enum Dir {
    N,
    E,
    S,
    W,
}

impl Dir {
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
}

#[derive(Debug)]
struct World {
    blocks: HashSet<Crd>,
    ups: HashSet<Crd>,
    downs: HashSet<Crd>,
    start: Crd,
}

impl World {
    fn from(grid: &[Vec<char>]) -> Self {
        let mut blocks = HashSet::new();
        let mut ups = HashSet::new();
        let mut downs = HashSet::new();
        let mut start = Crd(i16::MIN, i16::MIN);

        for (i, row) in grid.iter().enumerate() {
            for (j, cell) in row.iter().enumerate() {
                let p = Crd(i as i16, j as i16);
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

    let in_bounds = |p: Crd| -> bool {
        let h = grid.len() as i16;
        assert!(!grid.is_empty());
        let w = grid[0].len() as i16;

        let Crd(i, j) = p;
        0 <= i && i < h && 0 <= j && j < w
    };

    let world = World::from(&grid);
    let mut result = State::new(world.start).alt;
    let mut q: VecDeque<State> = VecDeque::from([State::new(world.start)]);

    while let Some(u) = q.pop_front() {
        for v in world.adjacent_states(u) {
            if v.t <= 100 && in_bounds(v.crd) {
                result = result.max(v.alt);
                q.push_back(v);
            }
        }
    }

    println!("{}", result);
}
