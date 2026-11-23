use std::{
    collections::{HashMap, HashSet, VecDeque},
    io::{BufRead, stdin},
    iter::once,
};

use itertools::Itertools;

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
struct Crd(i8, i8);

impl Crd {
    fn from_indices(ro: usize, co: usize) -> Crd {
        Crd(ro as i8, co as i8)
    }
}

impl std::ops::Add<Crd> for Crd {
    type Output = Crd;

    fn add(self, o: Crd) -> Crd {
        Crd(self.0 + o.0, self.1 + o.1)
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
    fn all() -> [Dir; 4] {
        [Dir::N, Dir::E, Dir::S, Dir::W]
    }

    fn id(self) -> usize {
        Dir::all().into_iter().position(|x| x == self).unwrap()
    }

    fn delta(self) -> Crd {
        match self {
            Dir::N => Crd(-1, 0),
            Dir::E => Crd(0, 1),
            Dir::S => Crd(1, 0),
            Dir::W => Crd(0, -1),
        }
    }

    fn opposite(self) -> Dir {
        match self {
            Dir::N => Dir::S,
            Dir::E => Dir::W,
            Dir::S => Dir::N,
            Dir::W => Dir::E,
        }
    }
}

struct Maze {
    height: i8,
    width: i8,
    source: Crd,
    sink: Crd,
    walls: HashSet<Crd>,
    deposits: Vec<Crd>,
}

impl Maze {
    fn new(grid: Vec<Vec<char>>) -> Self {
        let crd_of = |a: char| -> Crd {
            for (i, row) in grid.iter().enumerate() {
                for (j, &cell) in row.iter().enumerate() {
                    if cell == a {
                        return Crd::from_indices(i, j);
                    }
                }
            }
            unreachable!()
        };

        let (walls, deposits) =
            grid.iter()
                .enumerate()
                .fold((HashSet::new(), vec![]), |(mut ws, mut ds), (i, row)| {
                    for (j, &cell) in row.iter().enumerate() {
                        match cell {
                            '#' => {
                                ws.insert(Crd::from_indices(i, j));
                            }
                            '@' => {
                                ds.push(Crd::from_indices(i, j));
                            }
                            _ => {}
                        };
                    }
                    (ws, ds)
                });

        Self {
            height: grid.len() as i8,
            width: grid[0].len() as i8,
            source: crd_of('S'),
            sink: crd_of('E'),
            walls,
            deposits,
        }
    }

    fn in_bounds(&self, crd: Crd) -> bool {
        0 <= crd.0 && crd.0 < self.height && 0 <= crd.1 && crd.1 < self.width
    }

    fn adjacent(&self, u: (Crd, Dir)) -> Vec<(Crd, Dir)> {
        let (u_crd, u_dir) = u;

        let possible_directions: Vec<_> = Dir::all()
            .into_iter()
            .filter(|&x| x != u_dir.opposite())
            .collect();

        possible_directions
            .into_iter()
            .filter_map(|v_dir| {
                let v_crd = u_crd + v_dir.delta();
                (self.in_bounds(v_crd) && !self.walls.contains(&v_crd)).then_some((v_crd, v_dir))
            })
            .collect()
    }

    fn distances_from(&self, u0: (Crd, Dir)) -> HashMap<(Crd, Dir), u16> {
        assert!(!self.walls.contains(&u0.0));
        assert!(self.in_bounds(u0.0));

        let mut dist: HashMap<(Crd, Dir), u16> = HashMap::from([(u0, 0)]);
        let mut q: VecDeque<(Crd, Dir)> = VecDeque::from([u0]);

        while let Some(u) = q.pop_front() {
            for v in self.adjacent(u) {
                if !dist.contains_key(&v) {
                    dist.insert(v, *dist.get(&u).unwrap() + 1);
                    q.push_back(v);
                }
            }
        }

        dist
    }
}

struct Meter {
    vs: Vec<Crd>,
    distances_by_source: Vec<HashMap<(Crd, Dir), u16>>,
}

impl Meter {
    fn measure_tour(&self, vertices_permutation: Vec<usize>) -> u16 {
        let ii: Vec<usize> = vertices_permutation
            .iter()
            .copied()
            .unique()
            .sorted()
            .collect();

        assert_eq!(ii, (0..self.vs.len()).collect::<Vec<usize>>());

        todo!()
    }
}

fn main() {
    let grid: Vec<Vec<char>> = stdin()
        .lock()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let maze = Maze::new(grid);

    let sources: Vec<(Crd, Dir)> = once(maze.source)
        .chain(maze.deposits.iter().copied())
        .flat_map(|u| {
            Dir::all()
                .into_iter()
                .filter_map(|dir| {
                    let v = u + dir.delta();
                    (maze.in_bounds(v) && !maze.walls.contains(&v)).then_some((u, dir))
                })
                .collect::<Vec<_>>()
        })
        .collect();

    let distances_by_source: Vec<HashMap<(Crd, Dir), u16>> =
        sources.iter().map(|&u| maze.distances_from(u)).collect();

    let meter = Meter {
        vs: once(maze.source)
            .chain(maze.deposits.iter().copied())
            .chain(once(maze.sink))
            .collect(),
        distances_by_source,
    };

    eprintln!("{}", meter.measure_tour((0..meter.vs.len()).collect()));
}
