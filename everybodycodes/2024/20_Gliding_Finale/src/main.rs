use ac_library::Dsu;
use std::{
    collections::{HashSet, VecDeque},
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
    fn all() -> Vec<Dir> {
        vec![Dir::N, Dir::E, Dir::S, Dir::W]
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

    fn up_clusters(&self) -> Vec<Vec<Crd>> {
        let mut dsu = Dsu::new(self.grid_height * self.grid_width);
        for u in self.ups.iter() {
            for dir in Dir::all() {
                let v = *u + dir.delta();
                if self.ups.contains(&v) {
                    let Crd(i, j) = u;
                    let Crd(r, c) = v;
                    dsu.merge(
                        *i as usize * self.grid_width + *j as usize,
                        r as usize * self.grid_width + c as usize,
                    );
                }
            }
        }

        dsu.groups()
            .into_iter()
            .filter_map(|ii| {
                if ii.len() > 3 {
                    Some(
                        ii.iter()
                            .map(|i| {
                                Crd((i / self.grid_width) as i16, (i % self.grid_width) as i16)
                            })
                            .collect::<Vec<_>>(),
                    )
                } else {
                    None
                }
            })
            .collect()
    }

    fn first_state_to_reach_an_up_cluster(&self, cluster: &[Crd]) -> State {
        let mut visited: HashSet<Crd> = HashSet::from([self.start]);
        let mut q: VecDeque<State> = VecDeque::from([State::new(self.start)]);

        while let Some(u) = q.pop_front() {
            for v in self
                .adjacent_states(u)
                .into_iter()
                .filter(|s| !visited.contains(&s.crd))
                .collect::<Vec<_>>()
            {
                if cluster.contains(&v.crd) {
                    return v;
                }
                visited.insert(v.crd);
                q.push_back(v);
            }
        }
        panic!()
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
    let approach_states = world
        .up_clusters()
        .into_iter()
        .map(|c| world.first_state_to_reach_an_up_cluster(&c))
        .collect::<Vec<_>>();

    let result = approach_states
        .into_iter()
        .map(|s| s.alt + (100 - s.t as i16))
        .max()
        .unwrap();

    println!("{}", result);
}
