use std::{
    collections::{HashMap, HashSet, VecDeque},
    io::{BufRead, stdin},
    iter::once,
};

use itertools::Itertools;

const INF: u16 = 55_555;

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

struct Optimizer {
    source: (Crd, Dir),
    vs: Vec<Crd>,
    adjacent_distances: HashMap<(Crd, Dir, Crd), [u16; 4]>,
    memo: HashMap<(u32, usize, Dir), u16>,
}

impl Optimizer {
    fn distance(&self, u: (Crd, Dir), v: (Crd, Dir)) -> u16 {
        let (u_crd, u_dir) = u;
        let (v_crd, v_dir) = v;
        let ws = self.adjacent_distances.get(&(u_crd, u_dir, v_crd)).unwrap();
        ws[v_dir.id()]
    }

    fn recur(&mut self, vs_bits: u32, i_last_v: usize, last_dir: Dir) -> u16 {
        assert_eq!(vs_bits & (1 << i_last_v), 1 << i_last_v);

        if let Some(w) = self.memo.get(&(vs_bits, i_last_v, last_dir)) {
            *w
        } else {
            let result = if vs_bits.count_ones() == 1 {
                self.distance(self.source, (self.vs[i_last_v], last_dir))
            } else {
                let n = self.vs.len();

                let uu: Vec<(usize, Dir)> = (0..n)
                    .filter(|&i| ((1 << i) & (vs_bits ^ (1 << i_last_v))) == (1 << i))
                    .cartesian_product(Dir::all())
                    .collect();

                uu.into_iter()
                    .filter_map(|(i, dir)| {
                        let last_leg =
                            self.distance((self.vs[i], dir), (self.vs[i_last_v], last_dir));

                        (last_leg < INF)
                            .then(|| last_leg + self.recur(vs_bits ^ (1 << i_last_v), i, dir))
                    })
                    .min()
                    .unwrap_or(INF)
            };

            self.memo.insert((vs_bits, i_last_v, last_dir), result);
            result
        }
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
                .map(|dir| (u, dir))
                .collect::<Vec<_>>()
        })
        .collect();

    let adjacent_distances: HashMap<(Crd, Dir, Crd), [u16; 4]> =
        sources
            .into_iter()
            .fold(HashMap::new(), |mut agg, (u_crd, u_dir)| {
                for ((v_crd, v_dir), w) in maze.distances_from((u_crd, u_dir)) {
                    agg.entry((u_crd, u_dir, v_crd))
                        .and_modify(|ws| {
                            ws[v_dir.id()] = w;
                        })
                        .or_insert({
                            let mut ws = [INF, INF, INF, INF];
                            ws[v_dir.id()] = w;
                            ws
                        });
                }

                agg
            });

    let mut opt = Optimizer {
        source: (maze.source, Dir::E),

        vs: maze
            .deposits
            .iter()
            .copied()
            .chain(once(maze.sink))
            .collect(),

        adjacent_distances,
        memo: HashMap::new(),
    };

    let n = opt.vs.len();

    let result = opt.recur((1 << n) - 1, n - 1, Dir::E);
    println!("{result}");
}
