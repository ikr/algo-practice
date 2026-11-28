use std::{
    collections::{HashMap, HashSet, VecDeque},
    io::{BufRead, stdin},
    iter::once,
};

const INF: u16 = 55_555;
const NUM_TARGET_DEPOSITS: usize = 2026;

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

    fn from_id(id: usize) -> Dir {
        match id {
            0 => Dir::N,
            1 => Dir::E,
            2 => Dir::S,
            3 => Dir::W,
            _ => unreachable!(),
        }
    }

    fn id(self) -> usize {
        match self {
            Dir::N => 0,
            Dir::E => 1,
            Dir::S => 2,
            Dir::W => 3,
        }
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

    fn immediate_distances_from(&self, u0: (Crd, Dir)) -> HashMap<(Crd, Dir), u16> {
        assert!(!self.walls.contains(&u0.0));
        assert!(self.in_bounds(u0.0));

        let mut dist: HashMap<(Crd, Dir), u16> = HashMap::from([(u0, 0)]);
        let mut q: VecDeque<(Crd, Dir)> = VecDeque::from([u0]);

        while let Some(u) = q.pop_front() {
            for v in self.adjacent(u) {
                if !dist.contains_key(&v) {
                    dist.insert(v, *dist.get(&u).unwrap() + 1);

                    if !self.deposits.contains(&v.0) {
                        q.push_back(v);
                    }
                }
            }
        }

        dist
    }
}

struct Optimizer {
    source: (Crd, Dir),
    vs: Vec<Crd>,
    immediate_distances: HashMap<(Crd, Dir, Crd, Dir), u16>,
}

impl Optimizer {
    fn distance(&self, u: (Crd, Dir), v: (Crd, Dir)) -> u16 {
        let (u_crd, u_dir) = u;
        let (v_crd, v_dir) = v;

        *self
            .immediate_distances
            .get(&(u_crd, u_dir, v_crd, v_dir))
            .unwrap_or(&INF)
    }

    fn min_time_to_collect_enough_deposits(&self) -> u16 {
        let n = self.vs.len();

        // dp[i][j][k] is the minimal time to collect i deposits ending up
        // at the coordinate vs[j] facing in the direction k.
        let mut dp: Vec<Vec<Vec<u16>>> = vec![vec![vec![INF; 4]; n]; NUM_TARGET_DEPOSITS + 10];

        for (j, &v) in self.vs.iter().enumerate() {
            for (k, d) in Dir::all().into_iter().enumerate() {
                dp[1][j][k] = self.distance(self.source, (v, d));
            }
        }

        for i in 1..dp.len() - 1 {
            for j in 0..n {
                for k in 0..4 {
                    if dp[i][j][k] < INF {
                        for jj in 0..n {
                            for kk in 0..4 {
                                if !(j == jj && k == kk)
                                    && let w = self.distance(
                                        (self.vs[j], Dir::from_id(k)),
                                        (self.vs[jj], Dir::from_id(kk)),
                                    )
                                    && w < INF
                                {
                                    dp[i + 1][jj][kk] = dp[i + 1][jj][kk].min(dp[i][j][k] + w);
                                }
                            }
                        }
                    }
                }
            }
        }

        (NUM_TARGET_DEPOSITS..dp.len())
            .map(|i| dp[i][n - 1][Dir::E.id()])
            .min()
            .unwrap()
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

    let immediate_distances: HashMap<(Crd, Dir, Crd, Dir), u16> =
        sources
            .into_iter()
            .fold(HashMap::new(), |mut agg, (u_crd, u_dir)| {
                for ((v_crd, v_dir), w) in maze.immediate_distances_from((u_crd, u_dir)) {
                    agg.insert((u_crd, u_dir, v_crd, v_dir), w);
                }

                agg
            });

    let opt = Optimizer {
        source: (maze.source, Dir::E),

        vs: maze
            .deposits
            .iter()
            .copied()
            .chain(once(maze.sink))
            .collect(),

        immediate_distances,
    };

    println!("{}", opt.min_time_to_collect_enough_deposits());
}
